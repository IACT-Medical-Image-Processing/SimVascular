/* Copyright (c) Stanford University, The Regents of the University of
 *               California, and others.
 *
 * All Rights Reserved.
 *
 * See Copyright-SimVascular.txt for additional details.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS
 * IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED
 * TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 * PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER
 * OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

// The sv4guiSimulationPreferencePage class is used to process information 
// about the location of the solver binaries (svpre, svsolver and svpost) 
// and the mpiexec binary used to execute a simulation presented in the 
// 'Preferences->SimVascular Simulation' panel. 
//
// sv4guiSimulationPreferencePage methods are used to 
//
//     1) Process GUI events 
//
//     2) Set the values of the solver binaries in the MITK database 
//
// The MITK database provides persistence for solver binary values between 
// SimVascular sessions.
//
// The values of the solver binaries are set from the MITK database if it 
// exists. Otherwise they are set using their default values obtained using
// an sv4guiSimulationPreferences() object.
//
// Pressing the SimVascular Simulation' panel 'OK' button calls the PerformOk() 
// method which saves the solver binary values into the MITK database.
//  

#include "sv4gui_SimulationPreferencePage.h"
#include "ui_sv4gui_SimulationPreferencePage.h"

#include <berryIPreferencesService.h>
#include <berryPlatform.h>

#include <mitkExceptionMacro.h>

#include <QFileDialog>
#include <QMessageBox>
#include <QProcess>

//--------------------------------
// sv4guiSimulationPreferencePage
//--------------------------------
// Constructor.
//
sv4guiSimulationPreferencePage::sv4guiSimulationPreferencePage() : m_Preferences(nullptr), 
    m_Ui(new Ui::sv4guiSimulationPreferencePage) , m_Control(nullptr)
{
  // Set the default locations of the solver binaries.
  m_DefaultPrefs = sv4guiSimulationPreferences();
}

sv4guiSimulationPreferencePage::~sv4guiSimulationPreferencePage()
{
}

//---------------------------
// InitializeSolverLocations
//---------------------------
// Find the location of solver binaries and mpiexec.
//
// The the full binary path is displayed in the SimVascular 
// 'Preferences->SimVascular Simulations' page and used to 
// execute a simulation.
//
// If the values for the binaries and mpiexec are not already
// set in the SimVascular MITK database then they set to their
// default values set in the sv4guiSimulationPreferences method.
//
void sv4guiSimulationPreferencePage::InitializeSolverLocations()
{
  // Set the solver binaries.
  SetPreSolver(); 
  SetSolver(); 
  SetPostSolver(); 

  // Set the mpiexec binary.
  SetMpiExec(); 

  // Set the MPI implementation. 
  SetMpiImplementation();
}

//---------------
// SetPostSolver
//---------------
// Set the post processing binary svpost.
//
void sv4guiSimulationPreferencePage::SetPostSolver()
{
  QString svPost = m_Ui->lineEditPostsolverPath->text().trimmed();

  if (!svPost.isEmpty()) {
    return;
  }

  svPost = m_DefaultPrefs.GetPostSolver();
  m_Ui->lineEditPostsolverPath->setText(svPost);
}

//------------
// SetMpiExec
//------------
// Set the location of the MPI mpiexec binary.
//
void sv4guiSimulationPreferencePage::SetMpiExec()
{
  QString mpiExec = m_Ui->lineEditMPIExecPath->text().trimmed();

  if (!mpiExec.isEmpty()) {
    return;
  }

  mpiExec = m_DefaultPrefs.GetMpiExec();
  m_Ui->lineEditMPIExecPath->setText(mpiExec);
}

//----------------------
// SetMpiImplementation 
//----------------------
// Set the installed MPI implementation.
//
void sv4guiSimulationPreferencePage::SetMpiImplementation()
{
  QString mpiExec = m_Ui->lineEditMPIExecPath->text().trimmed();

  if (mpiExec.isEmpty()) {
    return;
  }

  QString guiLabel("MPI Implementation: ");
  auto implStr = m_DefaultPrefs.GetMpiName();
  m_Ui->labelMPIImplementation->setText(guiLabel + implStr);
}

//------------------
// SetPresolverPath
//------------------
// Set the location of the svpre binary.
//
void sv4guiSimulationPreferencePage::SetPreSolver()
{
  QString svPresolver = m_Ui->lineEditPresolverPath->text().trimmed();

  if (!svPresolver.isEmpty()) {
    return;
  }

  svPresolver = m_DefaultPrefs.GetPreSolver();
  m_Ui->lineEditPresolverPath->setText(svPresolver);
}

//-----------
// SetSolver 
//-----------
// Set the svsolver binary, with or without mpi.
//
void sv4guiSimulationPreferencePage::SetSolver()
{
  QString svSolver = m_Ui->lineEditFlowsolverPath->text().trimmed();

  if (!svSolver.isEmpty()) {
    return;
  }

  bool useMPI = m_Ui->checkBoxUseMPI->isChecked();
  svSolver = m_DefaultPrefs.GetSolver();
  m_Ui->lineEditFlowsolverPath->setText(svSolver);
}

//-----------------
// CreateQtControl
//-----------------
//
void sv4guiSimulationPreferencePage::CreateQtControl(QWidget* parent)
{
    m_Control = new QWidget(parent);

    m_Ui->setupUi(m_Control);

    berry::IPreferencesService* prefService = berry::Platform::GetPreferencesService();
    Q_ASSERT(prefService);

    m_Preferences = prefService->GetSystemPreferences()->Node("/org.sv.views.simulation");

    connect( m_Ui->toolButtonPresolver, SIGNAL(clicked()), this, SLOT(SetPresolverPath()) );
    connect( m_Ui->toolButtonFlowsolver, SIGNAL(clicked()), this, SLOT(SetFlowsolverPath()) );
    connect( m_Ui->toolButtonMPIExec, SIGNAL(clicked()), this, SLOT(SetMPIExecPath()) );
    connect( m_Ui->toolButtonCustomTemplate, SIGNAL(clicked()), this, SLOT(SetCustomTemplatePath()) );
    connect( m_Ui->toolButtonPostsolver, SIGNAL(clicked()), this, SLOT(SetPostsolverPath()) );

    this->Update();

    // Set the locations of the solver binaries and mpiexec.
    InitializeSolverLocations();
}

//------------------
// SetPresolverPath
//------------------
// Process the GUI event to set the svpre path.
//
void sv4guiSimulationPreferencePage::SetPresolverPath()
{
    QString filePath = QFileDialog::getOpenFileName(m_Control, "Choose SimVascular Presolver");

    if (!filePath.isEmpty())
    {
        m_Ui->lineEditPresolverPath->setText(filePath);
    }
}

//-------------------
// SetFlowsolverPath
//-------------------
// Process the GUI event to set the svsolver path.
//
void sv4guiSimulationPreferencePage::SetFlowsolverPath()
{
    QString filePath = QFileDialog::getOpenFileName(m_Control, "Choose SimVascular Flowsolver");

    if (!filePath.isEmpty())
    {
        m_Ui->lineEditFlowsolverPath->setText(filePath);
    }
}

//----------------
// SetMPIExecPath
//----------------
// Process the GUI event to set the mpiexec path.
//
void sv4guiSimulationPreferencePage::SetMPIExecPath()
{
    QString filePath = QFileDialog::getOpenFileName(m_Control, "Choose MPIExec");

    if (!filePath.isEmpty())
    {
        m_Ui->lineEditMPIExecPath->setText(filePath);
    }
}

void sv4guiSimulationPreferencePage::SetCustomTemplatePath()
{
    QString filePath = QFileDialog::getOpenFileName(m_Control, "Choose Solver Custom Template");

    if (!filePath.isEmpty())
    {
        m_Ui->lineEditCustomTemplatePath->setText(filePath);
    }
}

//-------------------
// SetPostsolverPath 
//-------------------
// Process the GUI event to set the svpost path.
//
void sv4guiSimulationPreferencePage::SetPostsolverPath()
{
    QString filePath = QFileDialog::getOpenFileName(m_Control, "Choose SimVascular Postsolver");

    if (!filePath.isEmpty())
    {
        m_Ui->lineEditPostsolverPath->setText(filePath);
    }
}

QWidget* sv4guiSimulationPreferencePage::GetQtControl() const
{
    return m_Control;
}

void sv4guiSimulationPreferencePage::Init(berry::IWorkbench::Pointer)
{
}

void sv4guiSimulationPreferencePage::PerformCancel()
{
}

//-----------
// PerformOk
//-----------
// Process the 'OK' button GUI event.
//
bool sv4guiSimulationPreferencePage::PerformOk()
{
    // Get the solver paths from the GUI.
    QString presolverPath = m_Ui->lineEditPresolverPath->text().trimmed();
    QString flowsolverPath = m_Ui->lineEditFlowsolverPath->text().trimmed();
    bool useMPI = m_Ui->checkBoxUseMPI->isChecked();
    QString MPIExecPath = m_Ui->lineEditMPIExecPath->text().trimmed();
    bool useCustom = m_Ui->checkBoxUseCustom->isChecked();
    QString customTemplatePath = m_Ui->lineEditCustomTemplatePath->text().trimmed();
    QString postsolverPath = m_Ui->lineEditPostsolverPath->text().trimmed();

    // Set the values of the solver paths in the MITK database.
    m_Preferences->Put("presolver path", presolverPath);
    m_Preferences->Put("flowsolver path", flowsolverPath);
    m_Preferences->PutBool("use mpi", useMPI);
    m_Preferences->PutBool("use custom", useCustom);
    m_Preferences->Put("postsolver path", postsolverPath);

    // MPI implementation.
    m_Preferences->Put("mpi implementation", m_DefaultPrefs.GetMpiName());

    if(useMPI) {
        m_Preferences->Put("mpiexec path", MPIExecPath);
    }

    if(useCustom) {
        m_Preferences->Put("solver template path", customTemplatePath);
    }

    return true;
}

//--------
// Update
//--------
// Update the GUI with the solver path values from the
// MITK database.
//
void sv4guiSimulationPreferencePage::Update()
{
    m_Ui->lineEditPresolverPath->setText(m_Preferences->Get("presolver path",""));
    m_Ui->lineEditFlowsolverPath->setText(m_Preferences->Get("flowsolver path",""));
    m_Ui->checkBoxUseMPI->setChecked(m_Preferences->GetBool("use mpi", true));
    m_Ui->lineEditMPIExecPath->setText(m_Preferences->Get("mpiexec path",""));
    m_Ui->checkBoxUseCustom->setChecked(m_Preferences->GetBool("use custom", false));
    m_Ui->lineEditCustomTemplatePath->setText(m_Preferences->Get("solver template path",""));
    m_Ui->lineEditPostsolverPath->setText(m_Preferences->Get("postsolver path",""));
}


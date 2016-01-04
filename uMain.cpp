//---------------------------------------------------------------------------

#include <fmx.h>
#pragma hdrstop

#include "uMain.h"
// ---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource ("*.LgXhdpiPh.fmx", _PLAT_ANDROID)

TAccelerometerForm *AccelerometerForm;


// ---------------------------------------------------------------------------
__fastcall TAccelerometerForm::TAccelerometerForm(TComponent* Owner)
	: TForm(Owner)
	 {
}
// ---------------------------------------------------------------------------
void __fastcall TAccelerometerForm::FormCreate(TObject *Sender) {

	// start with no sensors
	lbAccelerationX->Visible = false;
	lbAccelerationY->Visible = false;
	lbAccelerationZ->Visible = false;
	lbAngleAccelX->Visible = false;
	lbAngleAccelY->Visible = false;
	lbAngleAccelZ->Visible = false;
	lbMotion->Visible = false;
	lbSpeed->Visible = false;
#ifdef _WIN32
	lbAccelerometerSensor->Text = "Simulator - no sensors";
	swAccelerometerSensorActive->Enabled = False;
#else
	FActiveSensor = NULL;
	TSensorManager::Current->Activate();
	TSensorArray LSensorArray = TSensorManager::Current->GetSensorsByCategory(TSensorCategory::Motion);
	FActiveSensor = (TCustomSensor*)LSensorArray[3];
 #endif

}
// ---------------------------------------------------------------------------
void __fastcall TAccelerometerForm::swAccelerometerSensorActiveSwitch
	(TObject *Sender)   {
	// activate or deactivate the reading of the accelerometer sensor
	MotionSensor1->Active = swAccelerometerSensorActive->IsChecked;
	Timer1->Enabled = swAccelerometerSensorActive->IsChecked;
	TSensorArray LSensorArray = TSensorManager::Current->GetSensorsByCategory(TSensorCategory::Motion);
	FActiveSensor = (TCustomSensor*)LSensorArray[3];
	if (Timer1->Enabled )
		 {
		   Timer2->Enabled = false;
		   lbAccelerationX->Visible = true; lbAccelerationY->Visible = true;lbAccelerationZ->Visible = true;

		 }
	 else
		 {
		 Timer2->Enabled = true;
		 Timer1->Enabled = false;
		 lbAccelerationX->Visible = false; lbAccelerationY->Visible = false;lbAccelerationZ->Visible = false;
		 }
}
// ---------------------------------------------------------------------------
void __fastcall TAccelerometerForm::Timer1Timer(TObject *Sender) {
  String TX, TY, TZ ;


	if (FActiveSensor != NULL) {
		  switch (FActiveSensor->Category) {
			case TSensorCategory::Motion:
			TX = GetInfoAboutMotionX(FActiveSensor);
			TY = GetInfoAboutMotionY(FActiveSensor);
			TZ = GetInfoAboutMotionZ(FActiveSensor);
			break;
		  }
		   TSensorArray LSensorArray = TSensorManager::Current->GetSensorsByCategory(TSensorCategory::Motion);

		  TCustomMotionSensor * ls = static_cast<TCustomMotionSensor*>(FActiveSensor);
		  if (!ls->Started)	ls->Start();
		  FActiveSensor = (TCustomSensor*)LSensorArray[0];
		  lbAccelerationX->Data = LSensorArray[0];

		  if (ls->AvailableProperties.Contains(TCustomMotionSensor::TProperty::AccelerationX)){
			 lbAccelerationX->Text = TX;
			 lbAccelerationY->Text = TY;
			 lbAccelerationZ->Text = TZ;
			 }
	 }
}
// ---------------------------------------------------------------------------
String __fastcall TAccelerometerForm::GetInfoAboutMotionX(TCustomSensor *ASensor) {
	String LValuesX = "";
	TCustomMotionSensor * ls = static_cast<TCustomMotionSensor*>(ASensor);
	if (!ls->Started)  ls->Start();
	if (ls->AvailableProperties.Contains(TCustomMotionSensor::TProperty::AccelerationX))
		LValuesX.sprintf(L"Acceleration X: %6.4f",ls->AccelerationX*10);
   return LValuesX;
 }
 // ---------------------------------------------------------------------------
 String __fastcall TAccelerometerForm::GetInfoAboutMotionY(TCustomSensor *ASensor) {
	String LValuesY = "";
	TCustomMotionSensor * ls = static_cast<TCustomMotionSensor*>(ASensor);
	if (!ls->Started)  ls->Start();
	if (ls->AvailableProperties.Contains(TCustomMotionSensor::TProperty::AccelerationY))
		LValuesY.sprintf(L"Acceleration Y: %6.4f",ls->AccelerationY*10);
   return LValuesY;
 }
 // ---------------------------------------------------------------------------
 String __fastcall TAccelerometerForm::GetInfoAboutMotionZ(TCustomSensor *ASensor) {
	String LValuesZ = "";
	TCustomMotionSensor * ls = static_cast<TCustomMotionSensor*>(ASensor);
	if (!ls->Started)  ls->Start();
	if (ls->AvailableProperties.Contains(TCustomMotionSensor::TProperty::AccelerationZ))
		LValuesZ.sprintf(L"Acceleration Z: %6.4f",ls->AccelerationZ*10);
   return  LValuesZ;
 }
// ---------------------------------------------------------------------------
void __fastcall TAccelerometerForm::Timer2Timer(TObject *Sender) {
 String ResultText;
	if (FActiveSensor != NULL) {
		   TSensorArray LSensorArray = TSensorManager::Current->GetSensorsByCategory(TSensorCategory::Motion);
		   FActiveSensor = (TCustomSensor*)LSensorArray[3];
		   TCustomMotionSensor * ls = static_cast<TCustomMotionSensor*>(FActiveSensor);
		   if (!ls->Started)	ls->Start();
	   }
}
//---------------------------------------------------------------------------



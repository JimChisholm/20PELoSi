//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
// $Id: B1DetectorConstruction.cc 94307 2015-11-11 13:42:46Z gcosmo $
//
/// \file B1DetectorConstruction.cc
/// \brief Implementation of the B1DetectorConstruction class

#include "B1DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4Element.hh"
#include "G4ElementTable.hh"


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::B1DetectorConstruction()
: G4VUserDetectorConstruction(),
  fScoringVolume(0)
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

B1DetectorConstruction::~B1DetectorConstruction()
{ }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4VPhysicalVolume* B1DetectorConstruction::Construct()
{  
  // Get nist material manager
  G4NistManager* nist = G4NistManager::Instance();
  
  // Envelope parameters
  //
  G4double env_sizeXY = 300*m, env_sizeZ = 300*m;
  G4Material* H20 = nist->FindOrBuildMaterial("G4_WATER");
G4Element* Carbon = new G4Element("Carbon", "C", 6, 12.011*g/mole);
  G4Element* Oxygen = new G4Element("Oxygen","O", 8, 16*g/mole);
  G4Material* MarsCO2 = new G4Material("MarsCO2", 0.00002*g/cm3, 2);
  MarsCO2->AddElement(Oxygen, 2);
  MarsCO2->AddElement(Carbon, 1);
  // Option to switch on/off checking of volumes overlaps
  //
  G4bool checkOverlaps = true;

  //     
  // World
  //
  G4double world_sizeXY = 1.2*env_sizeXY;
  G4double world_sizeZ  = 1.2*env_sizeZ;
  //G4Material* world_mat = nist->FindOrBuildMaterial("G4_CARBON_DIOXIDE");
  
  G4Box* solidWorld =    
    new G4Box("World",                       //its name
       0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);     //its size
      
  G4LogicalVolume* logicWorld =                         
    new G4LogicalVolume(solidWorld,          //its solid
                        MarsCO2,           //its material
                        "World");            //its name
                                   
  G4VPhysicalVolume* physWorld = 
    new G4PVPlacement(0,                     //no rotation
                      G4ThreeVector(),       //at (0,0,0)
                      logicWorld,            //its logical volume
                      "World",               //its name
                      0,                     //its mother  volume
                      false,                 //no boolean operation
                      0,                     //copy number
                      checkOverlaps);        //overlaps checking
                     
  //     
  // Envelope
  //  
  G4Box* solidEnv =    
    new G4Box("Envelope",                    //its name
        0.5*env_sizeXY, 0.5*env_sizeXY, 0.5*env_sizeZ); //its size
      
  G4LogicalVolume* logicEnv =                         
    new G4LogicalVolume(solidEnv,            //its solid
                        MarsCO2,             //its material
                        "Envelope");         //its name
               
  new G4PVPlacement(0,                       //no rotation
                    G4ThreeVector(),         //at (0,0,0)
                    logicEnv,                //its logical volume
                    "Envelope",              //its name
                    logicWorld,              //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                    checkOverlaps);          //overlaps checking
 

//G4Element* Sulfur = new G4Element("Sulfur","S", 16, 32.06*g/mole);
G4Element* Silicon = new G4Element("Silicon","Si", 14, 28.085*g/mole);
G4Element* Aluminum = new G4Element("Aluminum","Al", 13, 26.982*g/mole);
G4Element* Iron = new G4Element("Iron","Fe", 26, 55.845*g/mole);
G4Element* Magnesium = new G4Element("Magnesium","Mg", 12, 24.305*g/mole);
//G4Element* Manganese = new G4Element("Manganese", "Mn", 25, 54.938*g/mole);
G4Element* Calcium = new G4Element("Calcium","Ca", 20, 40.078*g/mole);
G4Element* Sodium = new G4Element("Sodium","Na", 11, 22.990*g/mole);
G4Element* Potassium = new G4Element("Potassium","K", 19, 26.982*g/mole);
//G4Element* Phosphorus = new G4Element("Phosphorus","P", 15, 30.974*g/mole);
//G4Element* Chlorine = new G4Element("Chlorine","Cl", 17, 35.45*g/mole);
//G4Element* Nitrogen = new G4Element("Nitrogen","N", 7, 14.007*g/mole);
//G4Element* Zinc = new G4Element("Zinc","Zn", 30, 65.38*g/mole);
//G4Element* Chromium = new G4Element("Chromium","Cr", 17, 35.45 *g/mole);
//G4Element* Titanium = new G4Element("Titanium","Ti", 22, 44.956*g/mole);
G4Element* Hydrogen = new G4Element("Hydrogen", "H", 1, 1.008*g/mole);
//G4Element* Carbon = new G4Element("Carbon", "C", 6, 12.011*g/mole);

//G4Material* CL = new G4Material("Chlorine", 3.2*g/cm3, 2); //do not know densities for sure as these are stp.
//CL->AddElement(Chlorine, 1); 

G4Material* Al2CaK2MgNa2O7 = new G4Material("Al2CaK2MgNa2O7", 1.7*g/cm3, 6);
Al2CaK2MgNa2O7->AddElement(Aluminum, 2);
Al2CaK2MgNa2O7->AddElement(Calcium, 1);
Al2CaK2MgNa2O7->AddElement(Potassium, 2);
Al2CaK2MgNa2O7->AddElement(Magnesium, 1);
Al2CaK2MgNa2O7->AddElement(Sodium, 2);
Al2CaK2MgNa2O7->AddElement(Oxygen, 7);

G4Material* SIO2 = new G4Material("Silicondioxide", 2.195*g/cm3, 2); 
SIO2->AddElement(Silicon, 1);
SIO2->AddElement(Oxygen, 2);

G4Material* Fe2O3 = new G4Material("Fe3Oxide", 5.25*g/cm3, 2);
Fe2O3->AddElement(Iron, 2);
Fe2O3->AddElement(Oxygen, 3);

G4Material* MMS2 = new G4Material("MarsRock", 1.62*g/cm3, 4);
MMS2->AddMaterial(SIO2, 51.2*perCent);
MMS2->AddMaterial(Fe2O3, 9.3*perCent); //Used internet source bc sara's is not complete
MMS2->AddMaterial(Al2CaK2MgNa2O7, 32.1*perCent);
MMS2->AddMaterial(H20, 7.4*perCent);


G4Material*PE = new G4Material("Polyethylene", 0.92*g/cm3, 2);
PE->AddElement(Hydrogen, 2);
PE->AddElement(Carbon, 4);

G4Material*shape3_mat = new G4Material("Brick", 1.544*g/cm3, 2);
shape3_mat->AddMaterial(PE, 20*perCent);
shape3_mat->AddMaterial(MMS2, 80*perCent); //p27 Sargent C6H10O2 formulas
//might add in oxygen O2 per Sargent p 27.

G4ThreeVector pos3 = G4ThreeVector(0*m, 0*m, 0*m);
//sphere shape
G4double shape3_pRmin = 7.5*m;
G4double shape3_pRmax = 8.5*m;
G4double shape3_pSPhi = 0*deg;
G4double shape3_pDPhi = 360*deg;
G4double shape3_pSTheta = 0*deg;
G4double shape3_pDTheta = 180*deg;
G4Sphere * solidShape3 = new G4Sphere("Shape3", shape3_pRmin, shape3_pRmax, shape3_pSPhi, shape3_pDPhi, shape3_pSTheta,
shape3_pDTheta);  // size and shape half dome I hope

G4LogicalVolume* logicShape3 = 
new G4LogicalVolume(solidShape3, // its solid
			shape3_mat, // its material
			"Shape3"); //its name
new G4PVPlacement(0, pos3, logicShape3,"Shape3", logicEnv, false, 0, checkOverlaps);
//fScoringVolume = logicShape3;
   
 
/*G4Material* shape2_mat = new G4Material("Regolith", 1.7*g/cm3, 14);
shape2_mat->AddMaterial(SIO2, 47.24*perCent); //added .61 % from CL to simplify
shape2_mat->AddMaterial(FeO, 12.18*perCent);
shape2_mat->AddMaterial(Fe2O3, 4.2*perCent);
shape2_mat->AddMaterial(MnO, 0.33*perCent);
shape2_mat->AddMaterial(MgO, 8.93*perCent);
shape2_mat->AddMaterial(CaO, 6.27*perCent);
shape2_mat->AddMaterial(Na2O, 3.02*perCent);
shape2_mat->AddMaterial(K2O, 0.41*perCent);
shape2_mat->AddMaterial(P2O5, 0.83*perCent);
shape2_mat->AddMaterial(Cr2O3, 0.36*perCent);
shape2_mat->AddMaterial(SO3, 4.9*perCent);
shape2_mat->AddMaterial(TiO2, 0.87*perCent);
shape2_mat->AddMaterial(Al2O3, 10.46*perCent);
//shape2_mat->AddMaterial(CL, 0.61*perCent);
*/
   
  G4ThreeVector pos2 = G4ThreeVector(0*m, -22*m, 0*m);
  // Trap shape       
  G4double shape2_dxa = 300*m, shape2_dxb = 300*m;
  G4double shape2_dya = 300*m, shape2_dyb = 300*m;
  G4double shape2_dz  = 20*m;      
  G4Trd* solidShape2 =    
    new G4Trd("Shape2",                      //its name
              0.5*shape2_dxa, 0.5*shape2_dxb, 
              0.5*shape2_dya, 0.5*shape2_dyb, 0.5*shape2_dz); //its size
                
  G4LogicalVolume* logicShape2 =                         
   new G4LogicalVolume(solidShape2,         //its solid
                        MMS2,          //its material
                        "Shape2");           //its name
  G4RotationMatrix* birdo = new G4RotationMatrix();
birdo->rotateX(90*deg);
//birdo->rotateY(90*deg);
//birdo->rotateZ(25*deg);            
  new G4PVPlacement(birdo,                       //no rotation
                    pos2,                    //at position
                    logicShape2,             //its logical volume
                    "Shape2",                //its name
                    logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                   checkOverlaps);          //overlaps checking

//shape 4
//
G4Material * shape4_mat = nist->FindOrBuildMaterial("G4_TISSUE_SOFT_ICRP");
G4ThreeVector pos4 = G4ThreeVector(0*m, 0*m, 0*m);
G4double shape4_pRmax = 0.5*m;
G4Orb * solidShape4 = new G4Orb("Shape4", shape4_pRmax);
G4LogicalVolume * logicShape4 = new G4LogicalVolume(solidShape4,         //its solid
                        shape4_mat,          //its material
                        "Shape4");
new G4PVPlacement(0,                       //no rotation
                    pos4,                    //at position
                    logicShape4,             //its logical volume
                    "Shape4",                //its name
                   logicEnv,                //its mother  volume
                    false,                   //no boolean operation
                    0,                       //copy number
                   checkOverlaps);          //overlaps checking
                
  fScoringVolume = logicShape4;


  //always return the physical World
  //
  return physWorld;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

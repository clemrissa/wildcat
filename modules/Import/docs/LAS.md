LAS format
==========

[Log ASCII Format](200~http://www.cwls.org/las/)

```
~Version
#MNEM .UNIT                VALUE  : DESCRIPTION
 VERS .                      2.0  : CWLS LOG ASCII STANDARD - VERSION 2.0
 WRAP .                       NO  : ONE LINE PER DEPTH STEP

~Well
#MNEM .UNIT                      VALUE  : DESCRIPTION
 STRT  .FT                         30.0  : Start Depth
 STOP  .FT                        594.0  : Stop Depth
 STEP  .FT                          0.1  : Step
 NULL  .                        -999.25  : Null Value
 COMP  .                        KGS-OGS  : Company
 WELL  .                    CURRENT # 1  : Well
 FLD   .                            fld  : Field
 SEC   .                             17  : Section
 TOWN  .                             5S  : Township (e.g. 42S)
 LOC   .                      5S-13E-17  : Location (Sec Town Range)
 LOC2  .                         SWNESE  : Location 2 (footages)
 CTRY  .                             US  : Country
 CNTY  .                       PONTOTOC  : County
 UWI   .                                 : Unique Well ID
 LIC   .                                 : Licence Number
 LATI  .                        N34.706  : Latitude
 GDAT  .                          NAD27  : Geodetic Datum
 Y     .                     4388921.03  : Y or North South coordinate
 UTM   .                           15.0  : UTM Location

~Parameter
#MNEM .UNIT           VALUE  : DESCRIPTION
 EGL   .M                775  : Ground Level Elevation
 EKB   .M                     : Kelly Bushing Elevation
 EDF   .F                     : Derrick Floor Elevation
 ERT   .F                     : Rotary Table Elevation
 TDL   .F             3837.0  : Total Depth Logger
 TDD   .               593.6  : Total Depth Driller

~Curve
#MNEM    .UNIT           VALUE  : DESCRIPTION
 DEPT     .FT                    : 1  DEPTH
 GAMMA    .API-GR                : 2  GAMMA RAY
 CALIPER  .INCH                  : 3  SHORT ARM CALIPER
 DEN(CDL) .G/CC                  : 5  COMPENSATED DENSITY
 RES(DG)  .OHM-M                 : 6  DEEP GUARD RES
 POR(NEU) .PERCENT               : 7  NEUTRON POROSITY
 DELTAT   .USEC/FT               : 3  DELTA TRAVEL TIME
 POTASIUM .PERCENT               : 3  POTASIUM
 URANIUM  .PPM                   : 4  URANIUM
 THORIUM  .PPM                   : 5  THORIUM

~ASCII
# DEPT GAMMA CALIPER DEN(CDL) RES(DG) POR(NEU) DELTAT POTASIUM URANIUM THORIUM
 30.0 302.56 3.6 2.29 231.02 50.22 179.0 3.09 36.89 12.49
 30.1 303.1 3.68 2.298 243.36 50.2 177.9 2.58 29.05 9.35
 30.2 313.48 3.62 2.3 257.56 50.2 177.3 2.77 25.29 8.14
 30.3 320.74 3.6 2.3 276.24 48.84 176.5 2.28 22.43 8.2
```

LAS Import
==========

Importing the LAS data is a complex process despite the apparent simplicity of the LAS format.

## Parsing

The parsing is trivial. It is enought to verify the completness of the LAS file.

## Data Validation and Mapping

- Error correction (typos, number formats, date field recognition)

- Units of measurement mapping
  Unit must be recognized and matched with available in database.

- Mandatory fields must not be empty.

- Mandatory fields must be 



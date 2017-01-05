; -- Horus.iss --
; Cassette logger for FEI's Polara microscope

#define HORUS_VERSION "0.99.6.0"
;; [guid]::NewGuid()
#define HORUS_UUID "{ab4c052f-2a67-46ac-ab32-b00f6e56ea2c}"

[Setup]
AppName=Horus Logger
UninstallDisplayName=Horus Logger
AppID={{#HORUS_UUID}
AppVersion={#HORUS_VERSION}
AppCopyright=Copyright (C) 2016-2017 Daniel Caujolle-Bert, BioEM Lab.
AppPublisher=BioEM Lab.
AppPublisherURL=https://c-cina.unibas.ch/bioem/
AppComments=Horus Logger {#HORUS_VERSION} {code:Architecture}
;AppUpdatesURL=http://www.example.com/updates.html
;AppContact=My Company Customer Support
LicenseFile=LICENSE.txt
WizardImageFile="Logos\BioEM-Lab-Vertical.bmp"
WizardSmallImageFile="Logos\Horus-Icon55_58.bmp"
SetupIconFile="Logos\Horus-Icon64.ico"
OutputBaseFilename=Horus-Logger-{#HORUS_VERSION}-x64
DefaultDirName={pf}\Horus Logger
DefaultGroupName=Horus Logger
UninstallDisplayIcon={uninstallexe}
Compression=lzma2
SolidCompression=yes
CloseApplications=yes
WindowVisible=no
;OutputDir=userdocs:Inno Setup Examples Output
; "ArchitecturesInstallIn64BitMode=x64" requests that the install be
; done in "64-bit mode" on x64, meaning it should use the native
; 64-bit Program Files directory and the 64-bit view of the registry.
; On all other architectures it will install in "32-bit mode".
ArchitecturesInstallIn64BitMode=x64
; Note: We don't set ProcessorsAllowed because we want this
; installation to run on all architectures (including Itanium,
; since it's capable of running 32-bit code too).

[Files]
; Place all x86 files here, first one should be marked 'solidbreak'
Source: "Horus\bin\Release\Horus.exe"; DestDir: "{app}"; DestName: "Horus.exe"; Check: Is64BitInstallMode
Source: "Horus\releaselibs_x64\*.dll"; DestDir: "{app}"; Check: Is64BitInstallMode
; Place all common files here, first one should be marked 'solidbreak'
Source: "LICENSE.txt"; DestDir: "{app}"; DestName: "Tool-LICENSE.txt"; Check: Is64BitInstallMode

[Icons]
Name: "{group}\Horus Logger"; Filename: "{app}\Horus.exe"
Name: "{commondesktop}\Horus Logger"; Filename: "{app}\Horus.exe"; Comment: "Horus Logger"
Name: "{group}\Uninstall Horus Logger"; Filename: "{uninstallexe}"
Name: "{group}\Horus's License"; Filename: "{app}\Horus-LICENSE.txt"

[Run]
;// User selected... these files are shown for launch after everything is done
;Filename: {app}\README.TXT; Description: View the README file; Flags: postinstall shellexec skipifsilent
Filename: "{app}\Horus.exe"; Description: Start Horus Logger; Flags: postinstall nowait skipifsilent unchecked

[Code]
// Some constants decl.
const
    RegKey = 'SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\' + '{#HORUS_UUID}' + '_is1';
    HorusVersion = '{#HORUS_VERSION}';

// Returns architecture string
function Architecture(str: String): String;
var
    S: String;
begin
    case ProcessorArchitecture of
        paX86:
            S := 'x86';
        paX64:
            S := 'x64';
        paIA64:
            S := 'Itanium';
    else
        S := 'Unrecognized';
    end;

  Result := S;
end;
    
// Stupid strcmp
function CompareVersion(str1, str2: String): Integer;
var
    temp1, temp2: String;

    
begin
    temp1 := str1;
    temp2 := str2;
    Result := CompareText(temp1, temp2);
end;

// It will uninstall different version than the current one, and exists the
// installer if identical version is already installed
function InitializeSetup(): Boolean;
var
    oldVersion: String;
    uninstaller: String;
    ErrorCode: Integer;
    
begin

  if RegKeyExists(HKEY_LOCAL_MACHINE, RegKey) then
      begin
      
          RegQueryStringValue(HKEY_LOCAL_MACHINE, RegKey, 'DisplayVersion', oldVersion);
          
          if (CompareVersion(oldVersion, HorusVersion) <> 0) then
              begin
                  //MsgBox('Uninstall version ' + oldVersion + ' of Horus Logger', mbInformation, MB_OK);    

                  RegQueryStringValue(HKEY_LOCAL_MACHINE, RegKey, 'UninstallString', uninstaller);
                  ShellExec('runas', uninstaller, '/SILENT', '', SW_HIDE, ewWaitUntilTerminated, ErrorCode);
                  Result := True;
                  
              end
          else
              begin
              
                  MsgBox('Version ' + oldVersion + ' of Horus Logger is already installed.'+#13#10+'This installer will exit.', mbInformation, MB_OK);    
                  Result := False;
                  
              end;
      end
  else
      begin
          //MsgBox('No uninstall of Horus Logger', mbInformation, MB_OK);    
          Result := True;
      end;
end;

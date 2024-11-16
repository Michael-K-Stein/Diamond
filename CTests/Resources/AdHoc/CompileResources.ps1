
function GetMsvcDir {
    param ()
    return Get-Item (
        Get-ChildItem -Path  "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC" | Where-Object -FilterScript { Test-Path -Path $_ -PathType Container } | Sort-Object -Descending | Select-Object -First 1
    )
}
$MSVCDir = GetMsvcDir

function Build-Resource {
    [CmdletBinding()]
    param (
        # Files to build
        [Parameter(Mandatory = $true)]
        [string[]]
        $Files,

        # Basename of output files
        [Parameter(Mandatory = $true)]
        [string]
        $Output   ,
        
        [Parameter(Mandatory = $false)]
        [string]
        $WindowsHeaders = $false
    )
    
    begin {
        New-Item -ItemType "Directory" -Name "out" -ErrorAction SilentlyContinue
    }

    process {
        if ($WindowsHeaders -eq $true) {
            $ClArgs = @(
                '/I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\ucrt"';
                '/I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\um"';
                '/I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\shared"';
                "/I`"$MSVCDir\include`"";
                "/I`"$MSVCDir\atlmfc\include`"";
                '/c';
                '/Zi';
                '/Od';
                '/Oi';
                "/Fd`"out\$Output.pdb`"";
                "/Fo`"out\$Output.obj`"";
            ) + $Files
        }
        Else {
            $ClArgs = @(
                '/I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\ucrt"';
                "/I`"$MSVCDir\include`"";
                '/c';
                '/Zi';
                '/Od';
                '/Oi';
                "/Fd`"out\$Output.pdb`"";
                "/Fo`"out\$Output.obj`"";
            ) + $Files
        }
      
        Write-Host $ClArgs

        Start-Process -FilePath "$MSVCDir\bin\Hostx64\x64\cl.exe" -ArgumentList $ClArgs -NoNewWindow -Wait
    }
    
    end {
        
    }
}

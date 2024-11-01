
$MSVCDir = "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Tools\MSVC\14.39.33519"

function Build-Resource {
    [CmdletBinding()]
    param (
        # Files to build
        [Parameter()]
        [string[]]
        $Files,

        # Basename of output files
        [Parameter()]
        [string]
        $Output
    )
    
    begin {
        New-Item -ItemType "Directory" -Name "out" -ErrorAction SilentlyContinue
    }

    process {
        $ClArgs = @(
            '/I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\ucrt"';
            '/I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\um"';
            '/I"C:\Program Files (x86)\Windows Kits\10\Include\10.0.22621.0\shared"';
            "/I`"$MSVCDir\include`"";
            '/c';
            '/Zi';
            '/Od';
            "/Fd`"out\$Output.pdb`"";
            "/Fo`"out\$Output.obj`"";
        ) + $Files

        Write-Host $ClArgs

        Start-Process -FilePath "$MSVCDir\bin\Hostx64\x64\cl.exe" -ArgumentList $ClArgs -NoNewWindow
    }
    
    end {
        
    }
}

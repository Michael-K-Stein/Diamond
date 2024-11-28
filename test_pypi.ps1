try {
    Push-Location pydia
    Start-Process -FilePath python -ArgumentList "..\setup\build_packaged_folder_structure.py", "..\x64\Release-3.12\pydia.pyd", "..\x64\Release-3.12\" , "..\setup\", "..\" -ErrorAction Break -Wait -NoNewWindow
    
    try {
        Pop-Location
        Push-Location x64\Release-3.12\package

        Start-Process -FilePath python -ArgumentList "setup.py", "clean", "--all" -ErrorAction Break -Wait -NoNewWindow
        Start-Process -FilePath python -ArgumentList "setup.py", "sdist", "bdist_wheel" -ErrorAction Break -Wait -NoNewWindow
        Start-Process -FilePath pip -ArgumentList "install", "dist/pydia3-0.0.1-py3-none-any.whl", "--force-reinstall" -ErrorAction Break -Wait -NoNewWindow
    }
    catch {}
    finally {
        Pop-Location
    }
}
catch {
    Pop-Location
}
finally {}

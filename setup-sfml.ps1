param(
    [ValidateSet('x64', 'Win32')]
    [string[]] $Architecture = @('x64', 'Win32')
)

$ErrorActionPreference = 'Stop'
$installRoot = Join-Path $PSScriptRoot '.sfml'
$packages = @{
    x64 = @{
        Url = 'https://www.sfml-dev.org/files/SFML-2.6.2-windows-vc17-64-bit.zip'
        Sha256 = 'F5995724604D74D06EFE89544315D11AC2D3C2D348854C6BE55A7A11FB7ECAD8'
    }
    Win32 = @{
        Url = 'https://www.sfml-dev.org/files/SFML-2.6.2-windows-vc17-32-bit.zip'
        Sha256 = '3D4A66CF4D36E7D895E7E12DD23532A9E9B70E1E61F3A7E2A6C518B367AB1D0D'
    }
}

New-Item -ItemType Directory -Force -Path $installRoot | Out-Null
foreach ($arch in $Architecture) {
    $package = $packages[$arch]
    $destination = Join-Path $installRoot $arch
    $sdk = Join-Path $destination 'SFML-2.6.2'
    if ((Test-Path (Join-Path $sdk 'include\SFML\Graphics.hpp')) -and
        (Test-Path (Join-Path $sdk 'lib\sfml-graphics.lib')) -and
        (Test-Path (Join-Path $sdk 'bin\sfml-graphics-2.dll'))) {
        Write-Host "SFML 2.6.2 ($arch) is already installed: $sdk"
        continue
    }

    $archive = Join-Path $installRoot "SFML-2.6.2-$arch.zip"
    Write-Host "Downloading SFML 2.6.2 ($arch)..."
    Invoke-WebRequest -Uri $package.Url -OutFile $archive -UseBasicParsing
    $actualHash = (Get-FileHash -LiteralPath $archive -Algorithm SHA256).Hash
    if ($actualHash -ne $package.Sha256) {
        throw "SHA-256 mismatch for $archive. Expected $($package.Sha256), got $actualHash."
    }

    Expand-Archive -LiteralPath $archive -DestinationPath $destination -Force
    Remove-Item -LiteralPath $archive
    if (-not (Test-Path (Join-Path $sdk 'include\SFML\Graphics.hpp'))) {
        throw "SFML archive did not contain the expected SDK: $sdk"
    }
    Write-Host "Installed SFML 2.6.2 ($arch): $sdk"
}

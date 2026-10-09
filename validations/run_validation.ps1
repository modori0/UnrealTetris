# UnrealTetris 프로젝트 검증 스크립트
# PowerShell 스크립트로 실행 가능

# 1. 프로젝트 루트 확인
Write-Host "=== UnrealTetris 프로젝트 검증 ===" -ForegroundColor Cyan

# 프로젝트 파일 확인
$RequiredFiles = @(
    "UnrealTetris.uproject",
    "Source/UnrealTetris/UnrealTetris.Build.cs",
    "Source/UnrealTetris/UnrealTetris.cpp",
    "Source/UnrealTetris/UnrealTetris.h",
    "Source/UnrealTetris/UnrealTetrisGameMode.cpp",
    "Source/UnrealTetris/UnrealTetrisGameMode.h",
    "Source/UnrealTetris/UnrealTetrisPawn.cpp",
    "Source/UnrealTetris/UnrealTetrisPawn.h",
    "Source/UnrealTetris/UnrealTetrisPiece.cpp",
    "Source/UnrealTetris/UnrealTetrisPiece.h"
)

Write-Host "`n파일 존재 확인:" -ForegroundColor Yellow
$AllFilesExist = $true
foreach ($file in $RequiredFiles) {
    if (Test-Path $file) {
        Write-Host "[OK] $file" -ForegroundColor Green
    } else {
        Write-Host "[MISSING] $file" -ForegroundColor Red
        $AllFilesExist = $false
    }
}

if (-not $AllFilesExist) {
    Write-Host "`n[ERROR] 일부 파일이 누락되었습니다!" -ForegroundColor Red
    exit 1
}

# 2. .uproject 파일 JSON 검증
Write-Host "`n.uproject 파일 검증:" -ForegroundColor Yellow
$uproject = Get-Content "UnrealTetris.uproject" | ConvertFrom-Json
if ($uproject.FileVersion -and $uproject.EngineAssociation) {
    Write-Host "[OK] Unreal 프로젝트 파일 형식 확인" -ForegroundColor Green
    Write-Host "       Engine: $($uproject.EngineAssociation)" -ForegroundColor Gray
} else {
    Write-Host "[ERROR] .uproject 파일 형식 오류" -ForegroundColor Red
}

# 3. Git 상태 확인
Write-Host "`nGit 상태 확인:" -ForegroundColor Yellow
git status --short

Write-Host "`n=== 검증 완료 ===" -ForegroundColor Cyan
Write-Host "모든 검증이 통과했습니다. 이제 Unreal Engine에서 프로젝트를 열어 검증하실 수 있습니다." -ForegroundColor Yellow
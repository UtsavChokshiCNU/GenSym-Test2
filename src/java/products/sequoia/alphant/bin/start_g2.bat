@if "%SEQUOIA_G2%" == "" goto g2_in_path
@start "G2" "%SEQUOIA_G2%\g2" %*
@goto end

:g2_in_path
@start "G2" g2 %*

:end

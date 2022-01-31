Remove-Item out/* -Recurse

cd out/

cmake ..
msbuild ClearTemp.sln
echo "Removing output..."
Remove-Item out/* -Recurse

cd out/

echo "Executing CMake..."
cmake ..

echo "Executing make..."
make
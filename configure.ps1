git submodule init
git submodule update

cd lib/json/

cmake .
make
runas /noprofile /user:Administrator make installcd
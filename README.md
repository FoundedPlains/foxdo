```
Foxdo
suckless sudo

Do you sometimes feel like sudo takes long time or there is too much stuff to configure?

Then fear no more! foxdo has features like password checking, group and username checking, and also timeouted sessions, so until timeouted session ends, you don't have to type your password over and over again

Installing

git clone https://github.com/FoundedPlains/foxdo.git --recurse-submodules
cd foxdo
make
# make sure you run make install as root
make install

Uninstalling

# make sure you run make uninstall as root
make uninstall

Configuring
Open editor of your choice, and edit /etc/foxdo.foxconfig
```
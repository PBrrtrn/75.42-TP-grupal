sudo apt-get update && sudo apt-get install -y libyaml-cpp-dev libsdl2-ttf-dev

sudo mkdir /usr/lib/fiubastein3d
sudo mkdir /usr/lib/fiubastein3d/bin
sudo mkdir /usr/lib/fiubastein3d/maps
sudo mkdir /usr/lib/fiubastein3d/config

./build.sh
cd build
make

sudo cp ./Server /usr/lib/fiubastein3d/bin/
sudo cp ./Client /usr/lib/fiubastein3d/bin/
sudo cp ./WolfEditor /usr/lib/fiubastein3d/bin/
sudo cp ../scripts/ServerLauncher.sh /usr/lib/fiubastein3d/bin/
sudo cp ../scripts/ClientLauncher.sh /usr/lib/fiubastein3d/bin/
sudo cp ../scripts/EditorLauncher.sh /usr/lib/fiubastein3d/bin/
sudo cp ../maps/map1.yml /usr/lib/fiubastein3d/maps/
sudo cp ../maps/map-large.yml /usr/lib/fiubastein3d/maps/
sudo cp ../maps/x-room.yml /usr/lib/fiubastein3d/maps/
sudo cp ../server_config.yml /usr/lib/fiubastein3d/
sudo cp ../config/client_config.yml /usr/lib/fiubastein3d/config/client_config.yml
sudo cp -r ../assets/ /usr/lib/fiubastein3d/
sudo cp -r ../images/ /usr/lib/fiubastein3d/


grep -qxF 'alias fiubastein-server="sh /usr/lib/fiubastein3d/bin/ServerLauncher.sh"' ~/.bash_aliases || echo 'alias fiubastein-server="sh /usr/lib/fiubastein3d/bin/ServerLauncher.sh"' >> ~/.bash_aliases

grep -qxF 'alias fiubastein-client="sh /usr/lib/fiubastein3d/bin/ClientLauncher.sh"' ~/.bash_aliases || echo 'alias fiubastein-client="sh /usr/lib/fiubastein3d/bin/ClientLauncher.sh"' >> ~/.bash_aliases

grep -qxF 'alias fiubastein-editor="sh /usr/lib/fiubastein3d/bin/EditorLauncher.sh"' ~/.bash_aliases || echo 'alias fiubastein-editor="sh /usr/lib/fiubastein3d/bin/EditorLauncher.sh"' >> ~/.bash_aliases

#alias fiubastein-server="sh /usr/lib/fiubastein3d/bin/ServerLauncher.sh"
#alias fiubastein-client="sh /usr/lib/fiubastein3d/bin/ClientLauncher.sh"
#alias fiubastein-editor="sh /usr/lib/fiubastein3d/bin/EditorLauncher.sh"

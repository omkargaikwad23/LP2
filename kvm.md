```sudo apt update```


Install necessary libraries
```sudo apt install qemu-kvm libvirt-daemon-system libvirt-clients bridge-utils```


Add user to libvirt group
```sudo adduser omkar libvirt```


Add user to kvm group
```sudo adduser omakr kvm```


To check if virtualization is active or not
```virsh list --all```


Install virtualization manager
```sudo apt install virt-manager```


Run virt-manager
```sudo virt-manager```


Reference link
https://phoenixnap.com/kb/ubuntu-install-kvm
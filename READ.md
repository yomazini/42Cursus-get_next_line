# B2BR Overview

---

### **1. Linux Distribution Concepts (Debian vs Rocky)**

#### **What are Linux Distributions?**
- A Linux distribution is an operating system built on the Linux kernel, bundled with additional software like package managers, libraries, and utilities.

#### **Debian**
- **Overview**: Debian is a stable and community-driven Linux distribution. It’s known for its simplicity, reliability, and massive package repository.
- **Why Use It?** 
  - Ideal for beginners.
  - Extremely stable (great for servers).
  - Uses **APT** (Advanced Package Tool) for package management.
- **Real-world Example**: Web hosting companies often use Debian for their servers because it’s stable and widely supported.

#### **Rocky Linux**
- **Overview**: Rocky Linux is a free, community-driven alternative to Red Hat Enterprise Linux (RHEL). It’s designed for enterprises needing stability and long-term support.
- **Why Use It?**
  - Built for enterprise use.
  - Uses **YUM/DNF** for package management.
  - Includes SELinux for advanced security.
- **Real-world Example**: A financial institution might use Rocky Linux because it offers enterprise-level features like robust security and support for critical applications.

#### **Key Differences**
| **Aspect**         | **Debian**                  | **Rocky Linux**            |
|---------------------|-----------------------------|-----------------------------|
| **Target Audience** | Beginners, general-purpose | Enterprises, advanced users |
| **Package Manager** | APT                         | DNF/YUM                    |
| **Security Tools**  | AppArmor                   | SELinux                    |

---

### **2. Filesystem Hierarchy Standard (FHS)**

#### **What is FHS?**
- FHS defines the directory structure and their intended use in Linux. It ensures consistency across distributions.

#### **Key Directories**
- **`/` (Root)**: The base of the file system.
- **`/bin`**: Essential binaries (e.g., `ls`, `cp`).
- **`/etc`**: Configuration files (e.g., network settings).
- **`/var`**: Logs, variable data (e.g., `/var/log`).
- **`/home`**: User home directories.
- **`/usr`**: User programs (non-essential binaries).

#### **Real-world Example**
- If a server crashes, logs stored in `/var/log` (like `syslog`) can help diagnose the issue.

---

### **3. Disk Partitioning Techniques**

#### **What is Partitioning?**
- Partitioning divides a hard drive into separate sections to organize data and improve system management.

#### **Techniques**
1. **Manual Partitioning**:
   - You manually create partitions (e.g., `/`, `/home`, `/var`).
   - **Real-world Example**: A server admin allocates a separate `/var` partition to isolate log files and prevent them from filling up the main partition.

2. **Automatic Partitioning**:
   - Done by the installation program (e.g., guided install in Debian).
   - Good for beginners.

#### **Best Practices**
- Allocate separate partitions for critical directories (`/home`, `/var`, `/boot`) for better management.
- Use swap space for memory overflow.

---

### **4. Logical Volume Management (LVM)**

#### **What is LVM?**
- A method to manage disk space flexibly by creating virtual partitions over physical disks.

#### **Key Concepts**
- **Physical Volume (PV)**: Raw disk or partition.
- **Volume Group (VG)**: Combines multiple PVs into a single pool of storage.
- **Logical Volume (LV)**: Virtual partition created from a VG.

#### **Advantages**
- Resize partitions without unmounting them.
- Combine multiple drives into one logical storage pool.

#### **Real-world Example**
- An admin runs out of space in `/home`. With LVM, they can extend the LV without downtime by adding a new hard drive.

---

### **5. Basic System Architecture**

#### **What is System Architecture?**
- The design and structure of a system, including its hardware and software.

#### **Basic Components**
1. **Kernel**: Core of the operating system; manages resources and hardware communication.
2. **Shell**: Interface for users to interact with the system (e.g., Bash).
3. **Processes**: Programs running in the system.

#### **Real-world Example**
- In your Born2beRoot project, the monitoring script gathers data on CPU and memory usage. The kernel facilitates this by managing hardware resources.

---

### **6. Disk Partition Types**

#### **Primary Partition**
- Can hold operating systems or other data.
- Maximum of four per disk.
- **Real-world Example**: `/boot` is often stored in a primary partition to ensure the system can boot.

#### **Extended Partition**
- A container for logical partitions, overcoming the 4-partition limit.
- **Real-world Example**: If a server needs 6 partitions but the disk supports only 4 primary, you create an extended partition for the extra ones.

#### **Logical Partition**
- Resides within an extended partition.
- Used for organizing additional data (e.g., `/var`, `/home`).

---

### **Study Strategy**
1. **Practice Scenarios**: 
   - Install Debian or Rocky in VirtualBox, and experiment with partitioning and LVM.
2. **Visualization**: 
   - Create a diagram of the FHS and partition types for better memory retention.
3. **Relate Concepts**: 
   - Link LVM to real-world examples like resizing your phone storage with an SD card.

---

---

### **1. User and Group Management Commands**

#### **Why is it important?**
Users and groups help organize access to a Linux system. Each user and group has specific permissions, ensuring security and resource control.

#### **Key Commands**
1. **Creating a user**:  
   `sudo adduser username`  
   Creates a new user with a home directory.  
   **Example**: `sudo adduser john` creates a user named "john."

2. **Deleting a user**:  
   `sudo deluser username`  
   Removes the user but leaves files.  
   **Example**: `sudo deluser john`

3. **Creating a group**:  
   `sudo groupadd groupname`  
   **Example**: `sudo groupadd developers` creates a "developers" group.

4. **Adding a user to a group**:  
   `sudo usermod -aG groupname username`  
   **Example**: `sudo usermod -aG sudo john` gives "john" admin privileges.

5. **Checking group memberships**:  
   `groups username`  
   **Example**: `groups john` shows all groups "john" belongs to.

---

### **2. Sudo Configuration and Security**

#### **What is `sudo`?**
- **Sudo** allows users to run commands as a superuser (admin) temporarily.
- It's safer than directly using the `root` account.

#### **Securing `sudo`**
1. **Limiting `sudo` attempts**:  
   Set a limit on password attempts.  
   **Configuration**: Add this to `/etc/sudoers`:  
   ```plaintext
   Defaults        passwd_tries=3
   ```

2. **Custom error message**:  
   Show a custom message when a wrong password is entered.  
   **Configuration**:  
   ```plaintext
   Defaults        badpass_message="Access Denied: Check your password!"
   ```

3. **Restrict commands**:  
   Allow users to run specific commands only.  
   **Example**:  
   In `/etc/sudoers`:  
   ```plaintext
   john ALL=(ALL) NOPASSWD: /bin/systemctl
   ```  
   "John" can run `systemctl` commands without a password.

---

### **3. User Permissions and Ownership**

#### **File Ownership**
1. Every file in Linux has:
   - **Owner**: Usually the user who created it.
   - **Group**: A group with access to the file.

2. **Changing ownership**:  
   `sudo chown user:group filename`  
   **Example**: `sudo chown john:developers report.txt`  
   This assigns "john" as the owner and "developers" as the group.

#### **File Permissions**
- Linux uses **read (r)**, **write (w)**, and **execute (x)** permissions for:
  1. Owner
  2. Group
  3. Others  

**Example of Permissions**:  
`-rw-r--r--`  
- Owner can read/write.
- Group can read.
- Others can read.

#### **Changing Permissions**
1. `chmod` changes permissions.  
   **Example**: `chmod 755 script.sh`  
   - Owner: Read, write, execute.
   - Group: Read, execute.
   - Others: Read, execute.

2. **Symbolic mode**:  
   `chmod u+x file` adds execute (`x`) permission for the owner.  
   **Example**: `chmod g-w file` removes write (`w`) permission for the group.

---

### **4. Password Policies**

#### **Why are they important?**
Strong password policies protect systems from unauthorized access.

#### **Key Requirements for Born2beRoot**
1. Password expiration:  
   Set passwords to expire every 30 days.  
   **Command**:  
   ```bash
   sudo chage -M 30 username
   ```

2. Minimum days before change:  
   Prevent users from changing passwords too frequently (e.g., 2 days).  
   **Command**:  
   ```bash
   sudo chage -m 2 username
   ```

3. Password warnings:  
   Warn users 7 days before their password expires.  
   **Command**:  
   ```bash
   sudo chage -W 7 username
   ```

4. Password complexity:  
   Use the **`pam_pwquality`** module to enforce rules.  
   **Configuration**: Edit `/etc/security/pwquality.conf`:  
   ```plaintext
   minlen=10
   dcredit=-1
   ucredit=-1
   lcredit=-1
   ocredit=-1
   ```

---

### **5. Creating/Modifying Users and Groups**

#### **Examples**
1. **Create a user**:  
   ```bash
   sudo adduser jane
   ```
   This creates "jane" and a home directory `/home/jane`.

2. **Modify a user**:  
   Change "jane's" shell to `/bin/bash`:  
   ```bash
   sudo usermod -s /bin/bash jane
   ```

3. **Create a group**:  
   ```bash
   sudo groupadd admins
   ```

4. **Add "jane" to "admins"**:  
   ```bash
   sudo usermod -aG admins jane
   ```

---

### **6. SSH Key Authentication**

#### **What is it?**
SSH keys are a secure way to log in to a server without passwords. They use public-private key pairs.

#### **Steps**
1. **Generate an SSH key**:  
   Run this on your local machine:  
   ```bash
   ssh-keygen -t rsa -b 4096 -C "your_email@example.com"
   ```
   This creates two files:
   - Private key: `~/.ssh/id_rsa` (keep this secret).
   - Public key: `~/.ssh/id_rsa.pub`.

2. **Copy the public key to the server**:  
   ```bash
   ssh-copy-id user@server-ip
   ```

3. **Log in without a password**:  
   ```bash
   ssh user@server-ip
   ```

#### **Real-world Example**
Admins use SSH key authentication to securely access web servers without worrying about weak passwords.

---

### **7. SSH Configuration Security**

#### **Why secure SSH?**
SSH is a primary entry point for attackers. Proper configuration protects your server.

#### **Best Practices**
1. **Change the default port**:  
   Edit `/etc/ssh/sshd_config`:  
   ```plaintext
   Port 4242
   ```
   Restart SSH:  
   ```bash
   sudo systemctl restart ssh
   ```

2. **Disable root login**:  
   In `/etc/ssh/sshd_config`:  
   ```plaintext
   PermitRootLogin no
   ```

3. **Allow only specific users**:  
   In `/etc/ssh/sshd_config`:  
   ```plaintext
   AllowUsers john jane
   ```

4. **Disable password authentication** (use SSH keys):  
   ```plaintext
   PasswordAuthentication no
   ```

---

### **Real-world Example**
Imagine you're setting up a web server. You:
- Use SSH keys for secure access.
- Change the SSH port to 4242 to avoid common attacks on port 22.
- Disable root login to minimize damage if an attacker gains access.

---

### **Study Strategy**
- **Practice Commands**: Create test users and groups on a virtual machine.
- **Simulate Scenarios**: Set up SSH keys and secure the SSH configuration.
- **Visualize File Permissions**: Use diagrams or cheat sheets to remember the permissions structure.


---
---

### **1. UFW (Uncomplicated Firewall) Configuration**

#### **What is UFW?**
UFW is a simple tool for managing your Linux firewall. A firewall acts as a gatekeeper, deciding which data (network traffic) can enter or leave your computer.

#### **How to Remember?**
Imagine your house. A firewall is like your main door. You only allow trusted people (data) to enter while blocking strangers (hackers).

#### **Basic UFW Commands**
1. **Enable UFW**:  
   ```bash
   sudo ufw enable
   ```  
   **Real-world analogy**: Turning the lock on your front door.  

2. **Check Status**:  
   ```bash
   sudo ufw status
   ```  
   **Real-world analogy**: Checking if your door is locked or open.

3. **Allow Specific Traffic**:  
   ```bash
   sudo ufw allow 22
   ```  
   Allows SSH traffic on port 22.  
   **Real-world analogy**: Giving your friend a key to enter through a specific door.

4. **Deny Traffic**:  
   ```bash
   sudo ufw deny 80
   ```  
   Blocks traffic on port 80 (commonly used by websites).  
   **Real-world analogy**: Refusing entry to someone who isn’t invited.

5. **Disable UFW**:  
   ```bash
   sudo ufw disable
   ```  
   **Real-world analogy**: Leaving your front door wide open (not recommended!).

---

### **2. Basic Network Security Principles**

#### **Why is Network Security Important?**
Network security protects your system from unauthorized access or attacks, like burglars trying to sneak into your home.

#### **Principles**
1. **Least Privilege**:
   - Only give the minimum access necessary.  
   **Example**: Only open ports required for specific services (e.g., open port 4242 for SSH).

2. **Regular Updates**:
   - Keep your system and software updated.  
   **Example**: Update your Linux system regularly to patch vulnerabilities:
     ```bash
     sudo apt update && sudo apt upgrade
     ```

3. **Strong Passwords**:
   - Use complex passwords and SSH keys for authentication.

4. **Firewalls**:
   - Always keep the firewall active.  

#### **Real-world Analogy**:  
- Think of your network as a bank vault. Only trusted employees (specific ports/services) are allowed in, and security protocols (firewalls) keep burglars (hackers) out.

---

### **3. Port Management**

#### **What are Ports?**
- Ports are like doors in a building. Each door handles specific kinds of traffic.  
- For example:
  - **Port 22**: SSH (remote login).
  - **Port 80**: HTTP (websites).
  - **Port 443**: HTTPS (secure websites).

#### **Common Commands**
1. **List Open Ports**:  
   ```bash
   sudo ufw status numbered
   ```

2. **Allow a Port**:  
   ```bash
   sudo ufw allow 4242
   ```  
   Opens port 4242 for SSH (specific to Born2beRoot).

3. **Remove a Rule**:  
   ```bash
   sudo ufw delete allow 4242
   ```  
   Closes port 4242.  

#### **Real-world Example**:  
- Imagine a hotel with many doors (ports). Each door leads to a specific service. For instance:
  - Door 22: Staff entrance (SSH).
  - Door 80: Main entrance (HTTP).  
  The manager (you) decides which doors to keep open.

---

### **4. SSH Port Configuration**

#### **Why Change the Default SSH Port?**
- By default, SSH uses port 22, which is a common target for hackers. Changing the port adds an extra layer of security.

#### **How to Change the SSH Port**
1. Edit the SSH configuration file:  
   ```bash
   sudo nano /etc/ssh/sshd_config
   ```
2. Find the line:  
   ```plaintext
   #Port 22
   ```
3. Change it to a new port (e.g., 4242):  
   ```plaintext
   Port 4242
   ```
4. Save and restart SSH:  
   ```bash
   sudo systemctl restart ssh
   ```

#### **Real-world Analogy**:  
- It’s like changing the key to your house and moving the door to a hidden location. Hackers don’t know where to find it.

---

### **5. Network Service Management**

#### **What are Network Services?**
- These are programs that run on your server and communicate over the network, like SSH, web servers, or email servers.

#### **Key Commands**
1. **List Running Services**:  
   ```bash
   sudo systemctl list-units --type=service
   ```

2. **Start a Service**:  
   ```bash
   sudo systemctl start ssh
   ```

3. **Stop a Service**:  
   ```bash
   sudo systemctl stop ssh
   ```

4. **Check Service Status**:  
   ```bash
   sudo systemctl status ssh
   ```

#### **Real-world Example**:  
- Think of services as workers in a factory. You can hire (start), fire (stop), or check their performance (status).

---

### **6. Firewall Rules and Best Practices**

#### **Firewall Rules**
1. **Allow Traffic**:  
   Allow access to specific services or ports:  
   ```bash
   sudo ufw allow 443
   ```

2. **Block Traffic**:  
   Deny access to a specific port or service:  
   ```bash
   sudo ufw deny 21
   ```

3. **Limit Connections**:  
   Prevent brute-force attacks by limiting connection attempts:  
   ```bash
   sudo ufw limit ssh
   ```

#### **Best Practices**
- **Default Deny Policy**: Block all incoming traffic and only allow specific ports:  
  ```bash
  sudo ufw default deny incoming
  sudo ufw default allow outgoing
  ```

- **Enable Logging**: Track firewall activity for troubleshooting:  
  ```bash
  sudo ufw logging on
  ```

#### **Real-world Analogy**:  
- It’s like a VIP club. Only people on the guest list (specific ports) are allowed in, and a security log records who tried to enter.

---

### **7. Basic Network Troubleshooting**

#### **Key Tools**
1. **Ping**: Check if a server is reachable.  
   ```bash
   ping google.com
   ```

2. **Traceroute**: See the path data takes to reach a server.  
   ```bash
   traceroute google.com
   ```

3. **Netstat**: Show open ports and active connections.  
   ```bash
   netstat -tuln
   ```

4. **Curl**: Test if a website or service is working.  
   ```bash
   curl http://example.com
   ```

5. **Check UFW Logs**:  
   ```bash
   sudo tail -f /var/log/ufw.log
   ```

#### **Real-world Example**:  
- Imagine you can’t connect to your office Wi-Fi. You start troubleshooting:
  1. Ping the router to check if it’s online.
  2. Use traceroute to see if there’s an issue along the connection path.

---

### **How to Remember This?**
- **Firewall = Door Lock**: Only trusted traffic is allowed.  
- **Ports = Doors**: Each port is like a door for specific services.  
- **SSH = Key to Your House**: Change the lock (port) and use a better key (SSH keys).  
- **Services = Workers**: Manage who’s working and their access.  
- **Troubleshooting = Detective Work**: Tools like ping help you investigate problems.

---

---

### **1. System Monitoring Tools**

#### **What are System Monitoring Tools?**
- These tools give you information about how your system is running, including CPU usage, memory, and active processes.

#### **Common Tools**
1. **`top`**: Displays real-time information about running processes and system performance.
   - **Analogy**: It’s like looking at your phone’s battery usage screen to see which apps are using the most power.
   - **Command**:  
     ```bash
     top
     ```
     **Tip**: Press `q` to exit.

2. **`htop`**: A user-friendly version of `top` with better visuals.
   - **Analogy**: It’s like upgrading your black-and-white TV to a color one.
   - **Command**:  
     ```bash
     sudo apt install htop
     htop
     ```

3. **`vmstat`**: Shows system performance metrics like CPU and memory usage.
   - **Command**:  
     ```bash
     vmstat 1
     ```
     Refreshes every second.

4. **`iostat`**: Monitors input/output devices like disks.
   - **Command**:  
     ```bash
     iostat
     ```

#### **Real-world Example**:  
Imagine managing a restaurant. These tools are like watching the kitchen and waitstaff to ensure everything is running smoothly:
- **`top`**: Which chef (process) is busiest?
- **`vmstat`**: Is there enough storage space (ingredients)?
- **`htop`**: An easier way to monitor everyone.

---

### **2. Creating a Monitoring Bash Script**

#### **What is a Monitoring Script?**
- A script written in **bash** that automatically checks system performance and logs it.

#### **Simple Monitoring Script**
Here’s an example that monitors CPU usage, memory, and disk space:
```bash
#!/bin/bash
echo "System Monitoring Report"
echo "------------------------"
echo "Date: $(date)"
echo "CPU Usage: $(top -bn1 | grep "Cpu(s)" | awk '{print $2 + $4}')%"
echo "Memory Usage: $(free -m | awk 'NR==2{printf "%.2f%%", $3*100/$2 }')"
echo "Disk Usage: $(df -h / | awk 'NR==2 {print $5}')"
```

#### **How to Run It?**
1. Save it as `monitor.sh`.
2. Make it executable:  
   ```bash
   chmod +x monitor.sh
   ```
3. Run it:  
   ```bash
   ./monitor.sh
   ```

#### **Real-world Analogy**:  
This script is like an assistant who checks your car’s fuel, tire pressure, and engine temperature every morning and gives you a report.

---

### **3. System Logs (/var/log)**

#### **What Are System Logs?**
- Logs are files that record events happening on your system (errors, activity, etc.).
- They are stored in the **`/var/log`** directory.

#### **Important Logs**
1. **`/var/log/syslog`**: General system activity.
   - **Example**: Tracks messages from services and programs.
2. **`/var/log/auth.log`**: Authentication attempts (login successes/failures).
   - **Example**: See who tried to log in to your server.
3. **`/var/log/dmesg`**: Kernel-related messages.
   - **Example**: Hardware errors or driver issues.

#### **How to View Logs**
1. **View a Log**:  
   ```bash
   cat /var/log/syslog
   ```
2. **Follow a Log in Real Time**:  
   ```bash
   tail -f /var/log/syslog
   ```

#### **Real-world Analogy**:  
Think of logs as your car’s dashboard and maintenance history:
- **Auth.log**: Who has the keys to your car (logins)?
- **Syslog**: How the engine is performing (system activity).

---

### **4. Performance Metrics**

#### **What Are Performance Metrics?**
- These are measurements that show how well your system is running.

#### **Key Metrics**
1. **CPU Usage**:  
   - How busy your CPU is.  
   - **Command**:  
     ```bash
     top
     ```
   - **Real-world Analogy**: It’s like checking how hard your car engine is working.

2. **Memory Usage**:  
   - How much RAM is being used.  
   - **Command**:  
     ```bash
     free -m
     ```
   - **Real-world Analogy**: Think of RAM as the countertop in your kitchen; you need enough space to work efficiently.

3. **Disk Usage**:  
   - Available and used disk space.  
   - **Command**:  
     ```bash
     df -h
     ```
   - **Real-world Analogy**: Like checking how full your closet is before buying new clothes.

4. **Network Usage**:  
   - Data sent/received over the network.  
   - **Command**:  
     ```bash
     iftop
     ```

---

### **5. Process Management**

#### **What Is a Process?**
- A process is a program running on your system (e.g., a web server or a script).

#### **Key Commands**
1. **List Processes**:  
   ```bash
   ps aux
   ```
   **Real-world Analogy**: Think of this as your to-do list, showing everything currently happening.

2. **Kill a Process**:  
   ```bash
   kill PID
   ```
   Replace `PID` with the process ID (found using `ps aux` or `top`).
   **Example**:  
   ```bash
   kill 1234
   ```

3. **Force Kill**:  
   ```bash
   kill -9 PID
   ```

#### **Real-world Example**:  
Imagine a chef in a restaurant (process) who’s stuck or not working. Killing the process is like sending that chef home.

---

### **6. System Resource Monitoring**

#### **Why Monitor Resources?**
- To ensure the system has enough CPU, memory, and disk space to handle tasks.

#### **Tools for Resource Monitoring**
1. **`free`**: Check memory usage.  
   ```bash
   free -m
   ```

2. **`df`**: Check disk usage.  
   ```bash
   df -h
   ```

3. **`uptime`**: Check system load and uptime.  
   ```bash
   uptime
   ```
   - **Real-world Analogy**: It’s like seeing how tired you are after a long day.

---

### **7. Cron Jobs for Monitoring**

#### **What Are Cron Jobs?**
- Scheduled tasks that run automatically at specific times.

#### **How to Create a Cron Job**
1. Edit the crontab file:  
   ```bash
   crontab -e
   ```
2. Add a job to run your monitoring script every hour:  
   ```bash
   0 * * * * /path/to/monitor.sh >> /var/log/monitor.log
   ```
3. Save and exit.

#### **Real-world Analogy**:  
Cron jobs are like setting an alarm clock to remind you to check your house locks every evening.

---

### **Summary Table**

| **Concept**               | **Definition**                                                                                     | **Real-world Example**                                                                                         |
|---------------------------|---------------------------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------|
| **System Monitoring Tools** | Tools like `top`, `htop`, `vmstat` help check system health.                                      | Watching your phone’s battery and app usage.                                                                 |
| **Monitoring Script**      | A bash script to check system performance and log it.                                             | An assistant checking your car’s fuel, tires, and engine daily.                                               |
| **System Logs**            | Files in `/var/log` that record system events.                                                    | Your car’s maintenance history and dashboard alerts.                                                         |
| **Performance Metrics**    | Measurements like CPU, memory, disk usage, and network traffic.                                   | Checking how much storage or fuel your phone/car has left.                                                    |
| **Process Management**     | Commands to list, stop, or manage running processes.                                              | Sending a non-working chef (process) home.                                                                    |
| **Resource Monitoring**    | Tools to track available CPU, RAM, disk space, and more.                                          | Ensuring your kitchen countertop (RAM) has enough space to work efficiently.                                  |
| **Cron Jobs**              | Automated tasks that run at specific intervals.                                                   | Setting an alarm clock to check house security every evening.                                                 |

---

---

### **1. Systemd Service Management**

#### **What is Systemd?**
- Systemd is a system and service manager in Linux. It manages system processes and services (like starting/stopping programs).

#### **Key Commands**
1. **Start a Service**:  
   ```bash
   sudo systemctl start service_name
   ```  
   **Example**: `sudo systemctl start ssh` starts the SSH service.  

2. **Stop a Service**:  
   ```bash
   sudo systemctl stop service_name
   ```  
   **Example**: `sudo systemctl stop apache2` stops a web server.

3. **Restart a Service**:  
   ```bash
   sudo systemctl restart service_name
   ```

4. **Enable a Service** (start at boot):  
   ```bash
   sudo systemctl enable service_name
   ```  
   **Example**: Automatically start SSH after a reboot.

5. **Disable a Service**:  
   ```bash
   sudo systemctl disable service_name
   ```

6. **Check Service Status**:  
   ```bash
   sudo systemctl status service_name
   ```  
   **Example**: `sudo systemctl status ssh` shows if SSH is running.

#### **Real-world Analogy**:  
Systemd is like the manager of a store:
- **Start a service**: Telling employees (services) to start working.
- **Stop a service**: Sending them home.
- **Enable a service**: Automatically scheduling them to work every day.

---

### **2. APT Package Management**

#### **What is APT?**
- APT (**Advanced Package Tool**) is a tool in Debian-based Linux systems (like Debian or Ubuntu) used to install, update, and manage software.

#### **Key Commands**
1. **Update the Package List**:  
   ```bash
   sudo apt update
   ```  
   **Real-world Analogy**: Checking for the latest stock in your grocery store.

2. **Upgrade Installed Packages**:  
   ```bash
   sudo apt upgrade
   ```  
   **Real-world Analogy**: Replacing old items in your fridge with fresh ones.

3. **Install Software**:  
   ```bash
   sudo apt install package_name
   ```  
   **Example**: `sudo apt install apache2` installs a web server.  

4. **Remove Software**:  
   ```bash
   sudo apt remove package_name
   ```  
   **Example**: `sudo apt remove apache2` uninstalls the web server.

5. **Search for Software**:  
   ```bash
   apt search package_name
   ```

6. **Clean Unused Files**:  
   ```bash
   sudo apt autoremove
   ```  
   **Real-world Analogy**: Getting rid of expired food (unused packages).

---

### **3. Software Installation/Removal**

#### **What Is It?**
- Installing/removing software means adding or deleting applications from your system.

#### **Commands**
- To install:  
  ```bash
  sudo apt install software_name
  ```
- To remove:  
  ```bash
  sudo apt remove software_name
  ```

#### **Real-world Analogy**:  
Installing software is like adding new tools to your toolbox (e.g., installing a hammer to build things). Removing software is like getting rid of old, broken tools you no longer need.

---

### **4. Repository Configuration**

#### **What is a Repository?**
- A repository is like an online store where software packages are stored.

#### **Default Repository**
- Your system uses repositories listed in the file:  
  ```bash
  /etc/apt/sources.list
  ```

#### **Adding a New Repository**
1. Edit the repository file:  
   ```bash
   sudo nano /etc/apt/sources.list
   ```
2. Add a new line for the repository (you’ll get this from the software’s website).  
   **Example**: Adding a custom repository for Google Chrome:  
   ```bash
   deb [arch=amd64] http://dl.google.com/linux/chrome/deb/ stable main
   ```

3. Update the package list:  
   ```bash
   sudo apt update
   ```

#### **Real-world Analogy**:  
Repositories are like online stores:
- The **default repository** is like your usual supermarket.
- Adding a repository is like shopping at a specialty store for specific items.

---

### **5. Service Startup/Shutdown**

#### **What Is It?**
- Controlling whether a service (like SSH or Apache) starts, stops, or runs automatically.

#### **Commands**
- **Start a Service**:  
  ```bash
  sudo systemctl start service_name
  ```
- **Stop a Service**:  
  ```bash
  sudo systemctl stop service_name
  ```
- **Enable at Boot**:  
  ```bash
  sudo systemctl enable service_name
  ```
- **Disable at Boot**:  
  ```bash
  sudo systemctl disable service_name
  ```

#### **Real-world Analogy**:  
Starting/stopping a service is like turning appliances on/off at home:
- **Start the oven**: Start a service.
- **Turn off the fan**: Stop a service.
- **Auto-start coffee maker every morning**: Enable at boot.

---

### **6. Dependency Management**

#### **What Are Dependencies?**
- Dependencies are additional files or libraries that a program needs to work.

#### **How APT Handles Dependencies**
- APT automatically installs required dependencies when you install software.

#### **Example**
- Installing VLC Media Player might also install `libdvdcss` (a dependency for playing DVDs).

#### **Real-world Analogy**:  
Think of building furniture:
- The main piece (software) might need screws and a screwdriver (dependencies) to assemble it. Without them, it won’t work.

---

### **7. System Update Strategies**

#### **Why Update?**
- Updates fix bugs, patch security vulnerabilities, and improve performance.

#### **Best Practices**
1. **Update Package List Regularly**:  
   ```bash
   sudo apt update
   ```

2. **Upgrade Installed Software**:  
   ```bash
   sudo apt upgrade
   ```

3. **Full Upgrade** (handles package removals):  
   ```bash
   sudo apt full-upgrade
   ```

4. **Schedule Updates**:  
   Use cron jobs to automate updates:
   ```bash
   sudo crontab -e
   ```
   Add a line to update daily:  
   ```bash
   0 3 * * * apt update && apt upgrade -y
   ```

#### **Real-world Analogy**:  
Updating your system is like maintaining a car:
- **APT update**: Checking for recalls or updates.
- **APT upgrade**: Installing new parts to keep your car running smoothly.

---

### **Summary Table**

| **Concept**                 | **Definition**                                                                                     | **Real-world Analogy**                                                                                            |
|-----------------------------|---------------------------------------------------------------------------------------------------|-------------------------------------------------------------------------------------------------------------------|
| **Systemd Service Management** | Manages system processes and services (start, stop, enable).                                      | A store manager controlling which employees (services) work and when.                                             |
| **APT Package Management**   | Tool to install, update, and manage software on Debian systems.                                   | A grocery store where you get all your supplies (software).                                                       |
| **Software Installation/Removal** | Adding or removing software programs.                                                          | Adding a new tool (install) or throwing away broken tools (remove).                                               |
| **Repository Configuration** | Configuring online locations (repositories) to fetch software packages.                          | Shopping at a regular store (default repo) or a specialty store (custom repo).                                    |
| **Service Startup/Shutdown** | Controlling whether services (e.g., SSH) are running or start automatically.                     | Turning appliances (services) on/off or scheduling them to run automatically (like a coffee maker every morning). |
| **Dependency Management**    | Ensuring software has all the required files or libraries to work.                                | Building furniture where you need screws and tools (dependencies) to assemble the main piece (software).          |
| **System Update Strategies** | Regularly updating the system to keep it secure and efficient.                                    | Maintaining a car by checking for recalls and replacing old parts (updating packages).                            |

---

### **Practice Suggestions**
1. Use `systemctl` commands to start and stop services like SSH.
2. Try installing and removing software with APT.
3. Add a custom repository for a package (e.g., Google Chrome).
4. Schedule updates using `cron`.

---

---

### **1. AppArmor/SELinux Basics**

#### **What Are AppArmor and SELinux?**
- Both are Linux tools to enforce security policies on programs and processes, limiting what they can do.
- They operate on the principle of **Mandatory Access Control (MAC)**, meaning they define strict rules for access regardless of user permissions.

#### **Differences**
| **Feature**    | **AppArmor**                     | **SELinux**                     |
|-----------------|----------------------------------|----------------------------------|
| **Approach**    | Profile-based                   | Context-based                   |
| **Ease of Use** | Easier to configure             | More powerful but complex       |
| **Default Use** | Ubuntu, Debian                  | Red Hat, CentOS, Rocky Linux    |

#### **Example**
1. **AppArmor**:  
   Imagine a restaurant where chefs (programs) can only use ingredients and tools defined in their recipe (profile).  
   **Command**:  
   ```bash
   sudo aa-status
   ```  

2. **SELinux**:  
   Think of a bank vault. Each person (process) is assigned a specific role (context) and can only access certain areas.  
   **Command**:  
   ```bash
   getenforce
   setenforce 1  # Enable enforcing mode
   ```

---

### **2. Password Complexity Rules**

#### **What Are They?**
Rules that ensure passwords are strong enough to resist attacks.

#### **Best Practices**
1. Minimum length: At least 10 characters.
2. Must include:
   - Uppercase letters
   - Lowercase letters
   - Numbers
   - Symbols
3. Prevent reuse of old passwords.

#### **Implementation in Linux**
Edit the file **`/etc/security/pwquality.conf`**:  
```plaintext
minlen = 10
ucredit = -1  # Require at least one uppercase letter
lcredit = -1  # Require at least one lowercase letter
dcredit = -1  # Require at least one digit
ocredit = -1  # Require at least one special character
```

#### **Real-world Analogy**
Think of a strong password as a secure lock on your front door. The more complex the lock (password), the harder it is for burglars (hackers) to break in.

---

### **3. System Security Best Practices**

#### **What Are They?**
Guidelines to keep a Linux system secure.

#### **Key Practices**
1. **Keep the system updated**:  
   Install updates regularly to patch vulnerabilities:  
   ```bash
   sudo apt update && sudo apt upgrade
   ```
   **Analogy**: Updating your phone to fix bugs and improve security.

2. **Use a firewall**:  
   Enable UFW to control access:  
   ```bash
   sudo ufw enable
   ```

3. **Disable unnecessary services**:  
   Turn off unused services to reduce attack points:  
   ```bash
   sudo systemctl disable service_name
   ```

4. **Enable SSH key authentication**:  
   Use SSH keys instead of passwords for remote access.

#### **Real-world Analogy**
Imagine securing your home:
- **Updates**: Fix broken locks.
- **Firewall**: Build a fence.
- **Disable services**: Don’t leave extra doors open.

---

### **4. Audit and Logging**

#### **What Are Audit and Logging?**
- **Audit**: Tracks what actions are happening on the system (e.g., who accessed a file).  
- **Logging**: Records system events (e.g., errors, logins).

#### **Important Logs**
1. **System Log**: `/var/log/syslog`
2. **Authentication Log**: `/var/log/auth.log`
3. **Kernel Log**: `/var/log/kern.log`

#### **Audit Tool**
Install and use **auditd** to track activities:  
```bash
sudo apt install auditd
sudo systemctl start auditd
sudo auditctl -w /etc/passwd -p wa -k password_changes
```
- This monitors changes to the **`/etc/passwd`** file.

#### **Real-world Analogy**
- **Audit**: Like a security camera recording who enters and leaves your home.
- **Logs**: Like a diary documenting daily events.

---

### **5. Intrusion Detection Basics**

#### **What Is Intrusion Detection?**
It’s a way to identify unauthorized activity or potential threats on your system.

#### **Tools**
1. **Fail2ban**: Blocks IP addresses after too many failed login attempts.  
   ```bash
   sudo apt install fail2ban
   sudo systemctl start fail2ban
   ```
2. **Tripwire**: Detects changes to important system files.  
   ```bash
   sudo apt install tripwire
   ```

#### **Real-world Analogy**
- **Fail2ban**: Like a bouncer at a club blocking people who try to sneak in repeatedly.
- **Tripwire**: Like placing an alarm on your valuables to alert you if someone tampers with them.

---

### **6. Hardening Linux System**

#### **What Is Hardening?**
Strengthening the security of a Linux system to minimize vulnerabilities.

#### **Steps**
1. **Disable root SSH login**:  
   Edit **`/etc/ssh/sshd_config`**:  
   ```plaintext
   PermitRootLogin no
   ```

2. **Use strong passwords and SSH keys**.

3. **Restrict access to sensitive files**:  
   ```bash
   chmod 600 /etc/ssh/sshd_config
   ```

4. **Run a security scanner**:  
   Install **Lynis** to check system security:  
   ```bash
   sudo apt install lynis
   sudo lynis audit system
   ```

#### **Real-world Analogy**
Hardening is like upgrading your home security:
- Install better locks.
- Use cameras to monitor activity.
- Limit access to only trusted people.

---

### **7. Security Configurations**

#### **What Are Security Configurations?**
Settings that enhance system protection.

#### **Examples**
1. **Configure Firewall**:  
   Allow only necessary ports:  
   ```bash
   sudo ufw allow 4242
   sudo ufw deny 22
   ```

2. **Set File Permissions**:  
   Ensure sensitive files are protected:  
   ```bash
   chmod 600 /etc/passwd
   ```

3. **Enable SELinux or AppArmor**:  
   Set SELinux to enforcing mode:  
   ```bash
   setenforce 1
   ```

#### **Real-world Analogy**
Security configurations are like setting house rules:
- Only allow specific guests (firewall rules).
- Lock important rooms (file permissions).
- Monitor guests’ actions (SELinux/AppArmor).

---

### **Summary Table**

| **Concept**                | **Definition**                                                                 | **Real-world Analogy**                                                                                         |
|----------------------------|-------------------------------------------------------------------------------|---------------------------------------------------------------------------------------------------------------|
| **AppArmor/SELinux Basics** | Tools to limit what programs can do, even with user permissions.               | A restaurant where chefs or bank employees are limited to their specific tasks.                               |
| **Password Complexity Rules** | Ensures strong passwords to resist attacks.                                   | A strong door lock with unique keys.                                                                          |
| **System Security Best Practices** | Guidelines to secure a Linux system, like using firewalls and disabling unused services.    | Fixing locks, building fences, and keeping doors locked.                                                      |
| **Audit and Logging**       | Tracks and records system events and changes.                                  | Security cameras and diaries documenting daily events.                                                        |
| **Intrusion Detection Basics** | Identifies unauthorized activity using tools like Fail2ban and Tripwire.      | A bouncer blocking repeated intruders or an alarm on valuable items.                                          |
| **Hardening Linux System**  | Strengthening system security by limiting access and using security tools.     | Upgrading your home security with better locks and cameras.                                                   |
| **Security Configurations** | Settings like firewalls, permissions, and SELinux to protect your system.      | Setting house rules, locking doors, and monitoring activities.                                                |

---

### **How to Practice**
1. Set up AppArmor or SELinux in enforcing mode and test it.
2. Configure a strong password policy in **`/etc/security/pwquality.conf`**.
3. Install and configure Fail2ban to block brute-force login attempts.
4. Use Lynis to audit your system for vulnerabilities.

----


---

### **1. Web Server Setup (Lighttpd/Nginx)**

#### **What is a Web Server?**
A web server is software that delivers websites to users' browsers.  
- **Lighttpd**: Lightweight, fast, and resource-efficient (good for smaller projects).  
- **Nginx**: High-performance, widely used for handling heavy traffic.

#### **How to Set Up Lighttpd**
1. **Install Lighttpd**:  
   ```bash
   sudo apt install lighttpd
   ```

2. **Start the Server**:  
   ```bash
   sudo systemctl start lighttpd
   ```

3. **Access the Server**:  
   Open your browser and visit `http://localhost`.

#### **Real-world Analogy**
A web server is like a delivery driver:
- The driver (Lighttpd/Nginx) takes your restaurant’s food (website files) and delivers it to customers (users).

---

### **2. WordPress Installation**

#### **What is WordPress?**
WordPress is a free platform for building and managing websites.

#### **How to Install WordPress**
1. **Download WordPress**:  
   ```bash
   wget https://wordpress.org/latest.tar.gz
   tar -xvf latest.tar.gz
   ```

2. **Move WordPress to the Web Directory**:  
   ```bash
   sudo mv wordpress /var/www/html
   ```

3. **Set Permissions**:  
   ```bash
   sudo chown -R www-data:www-data /var/www/html/wordpress
   ```

4. **Configure WordPress**:  
   Access WordPress in your browser at `http://localhost/wordpress`.

#### **Real-world Analogy**
WordPress is like a content management tool for a blog:
- You write posts (content), and it handles the layout and publishing for your readers.

---

### **3. MariaDB/MySQL Configuration**

#### **What is MariaDB/MySQL?**
They are relational database management systems used to store and manage data for websites (e.g., user information, posts).

#### **How to Set Up MariaDB**
1. **Install MariaDB**:  
   ```bash
   sudo apt install mariadb-server
   ```

2. **Secure the Installation**:  
   ```bash
   sudo mysql_secure_installation
   ```

3. **Log into MariaDB**:  
   ```bash
   sudo mysql -u root -p
   ```

4. **Create a Database for WordPress**:  
   ```sql
   CREATE DATABASE wordpress;
   GRANT ALL PRIVILEGES ON wordpress.* TO 'wp_user'@'localhost' IDENTIFIED BY 'strongpassword';
   FLUSH PRIVILEGES;
   ```

#### **Real-world Analogy**
Think of MariaDB as a library:
- Books (data) are stored in organized shelves (tables), and librarians (SQL queries) help you find information quickly.

---

### **4. PHP Basic Configuration**

#### **What is PHP?**
PHP is a programming language used for building dynamic web pages (e.g., WordPress).

#### **How to Configure PHP**
1. **Install PHP**:  
   ```bash
   sudo apt install php php-mysql
   ```

2. **Check PHP Version**:  
   ```bash
   php -v
   ```

3. **Test PHP**:  
   Create a test file:  
   ```bash
   sudo nano /var/www/html/info.php
   ```  
   Add this code:  
   ```php
   <?php phpinfo(); ?>
   ```  
   Access it in your browser: `http://localhost/info.php`.

#### **Real-world Analogy**
PHP is like a chef in a restaurant:
- It takes raw ingredients (code) and creates a finished dish (dynamic web content).

---

### **5. Bonus Part Implementation Strategies**

#### **What is the Bonus Part?**
Extra tasks that go beyond the mandatory requirements of your project, such as:
- Setting up additional services.
- Securing and optimizing your configurations.

#### **Strategy Tips**
1. **Complete the Mandatory Part First**:  
   Ensure everything works perfectly before starting bonus tasks.

2. **Choose Simple Bonus Features**:  
   Focus on smaller, achievable tasks like setting up a simple web server.

3. **Document Everything**:  
   Write down every step for later reference.

#### **Real-world Analogy**
The bonus part is like extra credit in school:
- Finish your homework first, then do extra assignments to get a higher grade.

---

### **6. Additional Service Configurations**

#### **What Are Additional Services?**
These are extra features you can add to your server, such as:
- A mail server (e.g., Postfix).
- A caching service (e.g., Redis).

#### **Example: Installing Redis for Performance**
1. **Install Redis**:  
   ```bash
   sudo apt install redis
   ```

2. **Test Redis**:  
   ```bash
   redis-cli ping
   ```  
   You should see: `PONG`.

#### **Real-world Analogy**
Adding services is like upgrading your house:
- Redis is like adding a pantry for faster access to frequently used ingredients (cached data).

---

### **7. Performance Optimization**

#### **What Is It?**
Improving your server’s speed and resource usage.

#### **Tips for Optimization**
1. **Enable Compression**:  
   Reduce file sizes sent to users by enabling Gzip:  
   ```bash
   sudo nano /etc/nginx/nginx.conf
   ```  
   Add:  
   ```plaintext
   gzip on;
   ```

2. **Use Caching**:  
   Install and configure a caching service (e.g., Redis or Varnish).

3. **Optimize Database Queries**:  
   Use tools like **phpMyAdmin** to clean up unused tables.

4. **Monitor Resource Usage**:  
   Use `htop` to check for high CPU or RAM usage.

#### **Real-world Analogy**
Optimizing your server is like streamlining a restaurant:
- Use smaller menus (compression), prepare popular dishes in advance (caching), and track kitchen performance (monitoring).

---

### **Summary Table**

| **Concept**                        | **Definition**                                                                 | **Real-world Analogy**                                                                                          |
|------------------------------------|-------------------------------------------------------------------------------|----------------------------------------------------------------------------------------------------------------|
| **Web Server Setup**               | Software like Lighttpd or Nginx that delivers websites to users.              | A delivery driver bringing food (web content) to customers.                                                    |
| **WordPress Installation**         | Platform for building and managing websites.                                  | A blogging tool to organize and publish posts.                                                                 |
| **MariaDB/MySQL Configuration**    | A database system for storing and managing data.                              | A library where data is stored in organized shelves (tables).                                                  |
| **PHP Basic Configuration**        | Programming language for creating dynamic web pages.                          | A chef turning raw ingredients (code) into a finished dish (web content).                                      |
| **Bonus Part Strategies**          | Tips to implement extra project features effectively.                         | Completing extra-credit assignments after finishing homework.                                                  |
| **Additional Service Configurations** | Adding extra features like caching or mail servers.                           | Upgrading your house with a pantry or security cameras.                                                        |
| **Performance Optimization**       | Techniques to make the server faster and more efficient.                      | Streamlining a restaurant with smaller menus, pre-prepped dishes, and performance monitoring.                   |

---

### **How to Practice**
1. Set up a Lighttpd or Nginx web server on a virtual machine.
2. Install WordPress and connect it to a MariaDB database.
3. Experiment with Redis to improve caching.
4. Test server performance with tools like `htop` and make improvements.

---
---

### **1. Virtual Machine Signature**

#### **What is a VM Signature?**
- The **VM signature** is a unique identifier generated from your virtual disk file. This is used during the evaluation to verify that your submitted configuration matches your virtual machine.

#### **How to Generate It?**
1. Navigate to the folder where your VM is saved:
   - Linux: `~/VirtualBox VMs/`
   - Mac: `~/Library/Containers/com.utmapp.UTM/Data/Documents/`

2. Run a command to get the signature in SHA1 format:
   ```bash
   sha1sum your_vm_name.vdi
   ```

3. Copy the output (a long string of characters) to a file named `signature.txt`.

#### **Real-world Analogy**:
The signature is like your fingerprint—it uniquely identifies your machine and ensures no tampering occurs.

---

### **2. Hostname Configuration**

#### **What is a Hostname?**
- The **hostname** is the name of your virtual machine in the network. For the project, it must match your login with "42" appended (e.g., `john42`).

#### **How to Set Hostname?**
1. Edit the hostname file:  
   ```bash
   sudo nano /etc/hostname
   ```
   Add your hostname (e.g., `john42`).

2. Update the hosts file:  
   ```bash
   sudo nano /etc/hosts
   ```
   Add this line:  
   ```plaintext
   127.0.0.1    john42
   ```

3. Apply the changes:  
   ```bash
   sudo hostnamectl set-hostname john42
   ```

#### **Real-world Analogy**:
The hostname is like naming your Wi-Fi network (e.g., “HomeWiFi42”) so it can be identified easily on the network.

---

### **3. SSH Configuration with Port 4242**

#### **Why Use a Custom Port?**
- Using a non-default port (like 4242 instead of 22) improves security by reducing the risk of automated attacks.

#### **How to Configure SSH?**
1. Open the SSH configuration file:
   ```bash
   sudo nano /etc/ssh/sshd_config
   ```

2. Find and edit the line for the port:
   ```plaintext
   Port 4242
   ```

3. Restart the SSH service:
   ```bash
   sudo systemctl restart ssh
   ```

#### **Real-world Analogy**:
Changing the SSH port is like creating a hidden entrance for your house that only trusted people know about.

---

### **4. Encrypted Partitions Using LVM**

#### **Why Encryption?**
- Encrypted partitions protect sensitive data, ensuring it cannot be accessed without the proper key.

#### **How to Create Encrypted Partitions?**
1. Create a physical volume:
   ```bash
   sudo pvcreate /dev/sdX
   ```

2. Create a volume group:
   ```bash
   sudo vgcreate my_vg /dev/sdX
   ```

3. Create logical volumes:
   ```bash
   sudo lvcreate -L 10G -n my_lv my_vg
   ```

4. Encrypt the logical volume:
   ```bash
   sudo cryptsetup luksFormat /dev/my_vg/my_lv
   sudo cryptsetup open /dev/my_vg/my_lv my_encrypted_volume
   ```

#### **Real-world Analogy**:
Encryption is like putting your important documents in a safe that only you can unlock.

---

### **5. Sudo Configuration and Logs**

#### **Strict Sudo Rules**
1. **Limit Password Attempts**:  
   Add to `/etc/sudoers`:  
   ```plaintext
   Defaults        passwd_tries=3
   ```

2. **Custom Error Message**:  
   Add to `/etc/sudoers`:  
   ```plaintext
   Defaults        badpass_message="Access Denied: Please check your password!"
   ```

3. **Enable Sudo Logging**:  
   Ensure sudo logs are saved:  
   ```plaintext
   Defaults        logfile="/var/log/sudo/sudo.log"
   ```

#### **Real-world Analogy**:
Strict sudo rules are like setting up CCTV cameras to monitor who uses specific keys and when.

---

### **6. Monitoring Script with Bash**

#### **What Should It Do?**
The script must display system stats every 10 minutes, such as:
- CPU usage
- Memory usage
- Disk space
- Active connections

#### **Example Script**
```bash
#!/bin/bash
echo "System Monitoring Report"
echo "------------------------"
echo "Architecture: $(uname -m)"
echo "CPU Usage: $(top -bn1 | grep 'Cpu(s)' | awk '{print $2 + $4}')%"
echo "Memory Usage: $(free -m | awk 'NR==2{printf "%.2f%%", $3*100/$2}')"
echo "Disk Usage: $(df -h / | awk 'NR==2{print $5}')"
echo "Active Connections: $(netstat -an | grep ESTABLISHED | wc -l)"
```

#### **Real-world Analogy**:
This script is like a fitness tracker that checks your steps, heart rate, and sleep every few minutes.

---

### **7. Password Policy Configuration**

#### **Requirements**
1. Passwords must expire every 30 days.
2. Warnings must be sent 7 days before expiry.

#### **How to Configure Password Policies?**
1. Edit the file `/etc/login.defs`:
   ```plaintext
   PASS_MAX_DAYS   30
   PASS_MIN_DAYS   2
   PASS_WARN_AGE   7
   ```

2. Apply the policy to all users:
   ```bash
   sudo chage -M 30 -m 2 -W 7 username
   ```

#### **Real-world Analogy**:
Think of this as an ID card that expires after 30 days, requiring renewal to remain valid.

---

### **8. Defense Questions and Justifications**

#### **What to Prepare?**
During the project defense, you may be asked:
- Why did you choose Debian or Rocky Linux?
- What’s the difference between AppArmor and SELinux?
- How does your monitoring script work?
- Why use encrypted partitions?

#### **Tips**
1. **Understand** the reasoning behind your configurations.
2. **Practice Explaining** each step clearly.

#### **Real-world Analogy**:
Think of the defense as presenting your project to a client. Be ready to justify your choices and show how the system works.

---

### **Additional Topics to Explore**
- **FirewallD**: If using Rocky Linux, understand how to manage FirewallD instead of UFW.
- **Cron Jobs**: Automate tasks like running the monitoring script.
- **Saving VM States**: Learn how to save and revert VM states to avoid redoing configurations.

---

### **How to Prepare**
1. Practice all commands on a Virtual Machine to avoid errors during setup.
2. Review `/etc/sudoers`, `/etc/login.defs`, and `/etc/fstab` for configurations.
3. Simulate the defense by explaining your setup to a friend or recording yourself.

---

---

### **1. Virtual Machine Signature**
**Q1**: What is a virtual machine signature, and why is it important?  
**A1**: A VM signature is a unique identifier generated from the VM's virtual disk file using an SHA1 hash. It's important for verifying that the configuration you submitted matches your actual VM.

**Q2**: Which command generates the VM signature in Linux?  
**A2**:  
```bash
sha1sum your_vm_name.vdi
```

**Q3**: Where should the VM signature be saved for submission?  
**A3**: In a file named `signature.txt` at the root of your Git repository.

---

### **2. Hostname Configuration**
**Q4**: What is the purpose of a hostname in your Born2beRoot project?  
**A4**: The hostname uniquely identifies your virtual machine in a network and must match your login with "42" appended (e.g., `john42`).

**Q5**: Which file do you edit to change the hostname?  
**A5**:  
1. `/etc/hostname`  
2. `/etc/hosts`

**Q6**: How do you apply the hostname change immediately?  
**A6**:  
```bash
sudo hostnamectl set-hostname john42
```

---

### **3. SSH Configuration**
**Q7**: Why should you change the default SSH port from 22 to another port like 4242?  
**A7**: To reduce the risk of automated attacks by making it harder for attackers to find the SSH service.

**Q8**: Which file do you edit to change the SSH port?  
**A8**:  
```plaintext
/etc/ssh/sshd_config
```

**Q9**: How do you restart the SSH service after making changes?  
**A9**:  
```bash
sudo systemctl restart ssh
```

---

### **4. Encrypted Partitions with LVM**
**Q10**: Why is encryption important for partitions in Born2beRoot?  
**A10**: Encryption ensures sensitive data cannot be accessed without the proper key, protecting it even if the disk is stolen.

**Q11**: Which command initializes encryption on a logical volume?  
**A11**:  
```bash
sudo cryptsetup luksFormat /dev/my_vg/my_lv
```

**Q12**: How do you open an encrypted volume?  
**A12**:  
```bash
sudo cryptsetup open /dev/my_vg/my_lv my_encrypted_volume
```

---

### **5. Sudo Configuration**
**Q13**: What happens if a user enters an incorrect password three times while using sudo?  
**A13**: Access is denied after three incorrect attempts if you set the rule:  
```plaintext
Defaults        passwd_tries=3
```

**Q14**: Where are sudo logs saved by default if you enable logging?  
**A14**:  
```plaintext
/var/log/sudo/sudo.log
```

**Q15**: How can you set a custom error message for wrong sudo password attempts?  
**A15**: Add this line to `/etc/sudoers`:  
```plaintext
Defaults        badpass_message="Access Denied: Please check your password!"
```

---

### **6. Monitoring Script**
**Q16**: What is the purpose of the monitoring script in Born2beRoot?  
**A16**: It displays system stats like CPU usage, memory usage, disk usage, and active connections every 10 minutes.

**Q17**: Which command in a script gets the CPU usage?  
**A17**:  
```bash
top -bn1 | grep "Cpu(s)" | awk '{print $2 + $4}'
```

**Q18**: How do you make a monitoring script executable?  
**A18**:  
```bash
chmod +x monitor.sh
```

---

### **7. Password Policy**
**Q19**: What are the password requirements for the Born2beRoot project?  
**A19**:  
1. Passwords must expire every 30 days.  
2. A warning should be sent 7 days before expiration.  
3. Passwords must include uppercase, lowercase, numbers, and at least 10 characters.  
4. No more than 3 consecutive identical characters.

**Q20**: Which file is used to enforce password policies?  
**A20**:  
```plaintext
/etc/login.defs
```

**Q21**: How do you set password expiration for a user?  
**A21**:  
```bash
sudo chage -M 30 -m 2 -W 7 username
```

---

### **8. Defense Questions**
**Q22**: What are some differences between AppArmor and SELinux?  
**A22**:  
- AppArmor uses profiles to restrict programs, while SELinux uses contexts.  
- AppArmor is easier to configure but less powerful. SELinux is more complex and used in enterprise environments.

**Q23**: What is the purpose of creating two encrypted partitions using LVM?  
**A23**: It separates sensitive data and enhances security by encrypting it with LVM.

**Q24**: Why is the default SSH root login disabled?  
**A24**: To prevent unauthorized access, as root access gives complete control of the system.

---

### **9. Miscellaneous**
**Q25**: What is the importance of using UFW or FirewallD in this project?  
**A25**: It ensures only authorized network traffic (e.g., SSH on port 4242) is allowed, blocking unauthorized access.

**Q26**: How do you verify if UFW is active?  
**A26**:  
```bash
sudo ufw status
```

**Q27**: What is the purpose of the VM hostname during the defense?  
**A27**: The hostname helps evaluators identify your machine and ensures the naming convention matches project guidelines.

---

### **How to Use These Questions**
1. Quiz yourself daily using these questions.
2. Write down the answers without looking to strengthen memory.
3. Practice related commands on a virtual machine for hands-on learning.

---

Here are **active recall Q&A** to help you study each of the topics you've mentioned. These questions are grouped by day and will cover the material from **Day 1** to **Day 7**. They’ll help you strengthen your retention and understanding.

---

### **📅 Day 1: Linux Fundamentals & System Architecture**

**Q1**: What’s the key difference between Debian and Rocky Linux?  
**A1**: Debian is community-driven, stable, and recommended for beginners. Rocky Linux is an enterprise-level system, derived from Red Hat, designed for high-performance use.

**Q2**: What is the Filesystem Hierarchy Standard (FHS)?  
**A2**: The FHS defines the standard directory structure in Linux. It ensures consistency across distributions, with directories like `/bin`, `/etc`, `/var`, and `/home`.

**Q3**: What are the three main types of disk partitions?  
**A3**: Primary partitions, extended partitions, and logical partitions. Primary partitions hold operating systems; extended partitions are containers for logical ones.

**Q4**: What is Logical Volume Management (LVM)?  
**A4**: LVM allows for flexible disk management by grouping physical volumes into volume groups and creating logical volumes that can be resized.

**Q5**: What is the basic architecture of a Linux system?  
**A5**: It includes the **kernel**, which manages hardware; **shell**, which interacts with users; and **system libraries** that provide system functionalities.

**Q6**: What’s the difference between primary, extended, and logical partitions?  
**A6**: A primary partition holds the OS, an extended partition holds logical partitions, and logical partitions are created within an extended partition.

---

### **📅 Day 2: User & Access Management**

**Q7**: What is the command to add a user to a Linux system?  
**A7**: `sudo adduser username`

**Q8**: How do you modify a user's groups in Linux?  
**A8**: `sudo usermod -aG groupname username`

**Q9**: How do you configure sudo for strict security?  
**A9**: In `/etc/sudoers`, set rules like limiting the number of password attempts (`passwd_tries=3`), logging sudo actions, and restricting commands.

**Q10**: How can you enforce a strong password policy in Linux?  
**A10**: By editing `/etc/security/pwquality.conf` and `/etc/login.defs` to require a minimum length, complexity, and expiration policies.

**Q11**: How do you disable SSH root login?  
**A11**: In `/etc/ssh/sshd_config`, set `PermitRootLogin no` and restart SSH.

**Q12**: What’s the difference between public and private SSH keys?  
**A12**: The **private key** is kept secret on the client machine, while the **public key** is shared and placed on the server to allow authentication.

---

### **📅 Day 3: Network & Firewall Security**

**Q13**: What is UFW and how do you enable it?  
**A13**: UFW (Uncomplicated Firewall) is a simple firewall tool. Enable it using:  
```bash
sudo ufw enable
```

**Q14**: How do you open a specific port with UFW?  
**A14**:  
```bash
sudo ufw allow 4242
```

**Q15**: What’s the importance of changing the default SSH port?  
**A15**: Changing the SSH port reduces the risk of automated attacks targeting port 22.

**Q16**: How do you configure SSH to listen on port 4242?  
**A16**: In `/etc/ssh/sshd_config`, change the port to `4242` and restart SSH.

**Q17**: What’s the command to list active services on a Linux system?  
**A17**:  
```bash
sudo systemctl list-units --type=service
```

**Q18**: What’s the best practice for firewall rules?  
**A18**: Use a **default deny** rule and only open ports that are necessary, such as port 4242 for SSH.

**Q19**: How do you check if a port is open using UFW?  
**A19**:  
```bash
sudo ufw status
```

---

### **📅 Day 4: System Monitoring & Performance**

**Q20**: What does the `top` command show?  
**A20**: `top` displays real-time information about system processes, CPU, memory, and other system resources.

**Q21**: How can you create a simple bash script to monitor system performance?  
**A21**: Use commands like `top`, `free -m`, and `df -h` to fetch CPU, memory, and disk information, then output the results in a file or terminal.

**Q22**: Where are system logs stored in Linux?  
**A22**: System logs are stored in `/var/log`, with important logs like `syslog` and `auth.log`.

**Q23**: What’s the purpose of cron jobs?  
**A23**: Cron jobs automate tasks, like running a monitoring script at regular intervals.

**Q24**: What is the command to view the last 10 lines of a log file?  
**A24**:  
```bash
tail -n 10 /var/log/syslog
```

**Q25**: What is the `htop` command and how is it different from `top`?  
**A25**: `htop` is an interactive process viewer with better visuals and more control than `top`.

---

### **📅 Day 5: System Services & Package Management**

**Q26**: How do you start a service using systemd?  
**A26**:  
```bash
sudo systemctl start service_name
```

**Q27**: What command installs a package using APT?  
**A27**:  
```bash
sudo apt install package_name
```

**Q28**: What’s the purpose of `apt update` and `apt upgrade`?  
**A28**: `apt update` refreshes the package list, while `apt upgrade` installs the latest versions of installed packages.

**Q29**: How do you remove an unused package?  
**A29**:  
```bash
sudo apt remove package_name
```

**Q30**: What is the role of repositories in Linux?  
**A30**: Repositories are online stores that hold software packages. You configure them in `/etc/apt/sources.list`.

---

### **📅 Day 6: Security Policies & Compliance**

**Q31**: What is AppArmor and how does it secure applications?  
**A31**: AppArmor restricts what programs can do by defining profiles, limiting their access to resources.

**Q32**: What is SELinux and how is it different from AppArmor?  
**A32**: SELinux uses security contexts to enforce access control policies, while AppArmor uses application profiles. SELinux is more flexible but complex.

**Q33**: What is the purpose of hardening a Linux system?  
**A33**: Hardening strengthens system security by limiting potential attack vectors, such as disabling unused services and applying security patches.

**Q34**: What’s the command to enable SELinux?  
**A34**:  
```bash
setenforce 1
```

**Q35**: What’s the best way to track system activity and login attempts?  
**A35**: Use audit logs and the `/var/log/auth.log` file for monitoring system activity and user logins.

---

### **📅 Day 7: Bonus Part & Advanced Configurations**

**Q36**: What is the purpose of setting up a web server like Lighttpd or Nginx?  
**A36**: A web server serves websites to users. Lighttpd is lightweight, while Nginx is better suited for handling high-traffic websites.

**Q37**: How do you install WordPress on a Linux system?  
**A37**: Download WordPress, move it to the web directory (`/var/www/html`), set permissions, and configure the database.

**Q38**: What is MariaDB and how is it configured for WordPress?  
**A38**: MariaDB is a database server used for storing WordPress data. Create a database, assign a user, and grant privileges.

**Q39**: How do you configure PHP for WordPress?  
**A39**: Install PHP with MySQL support, configure it with the `php.ini` file, and ensure PHP modules like `php-mysql` are installed.

**Q40**: What is the role of performance optimization in web server management?  
**A40**: Performance optimization improves the speed and efficiency of your web server by using techniques like caching, compression, and optimizing database queries.

---

### **How to Use These Questions**
- **Test Yourself Regularly**: Use these questions as a quiz every few days.
- **Write Out Answers**: Writing the answers without looking at your notes strengthens memory.
- **Use Commands in Practice**: Run the commands in a virtual machine or real system to reinforce your understanding.

-----
#				 DONE
connect -url tcp:127.0.0.1:3121
targets -set -filter {jtag_cable_name =~ "Digilent Nexys4DDR 210292A4C432A" && level==0} -index 0
fpga -file /fs/student/ashishvyas/Downloads/Lab2B/Lab1B_handout/Lab1B/Lab1B.sdk/system_wrapper_hw_platform_0/system_wrapper.bit
configparams mdm-detect-bscan-mask 2
targets -set -nocase -filter {name =~ "microblaze*#0" && bscan=="USER2"  && jtag_cable_name =~ "Digilent Nexys4DDR 210292A4C432A"} -index 0
rst -system
after 3000
targets -set -nocase -filter {name =~ "microblaze*#0" && bscan=="USER2"  && jtag_cable_name =~ "Digilent Nexys4DDR 210292A4C432A"} -index 0
dow /fs/student/ashishvyas/Downloads/Lab2B/Lab1B_handout/Lab1B/Lab1B.sdk/project/Debug/project.elf
targets -set -nocase -filter {name =~ "microblaze*#0" && bscan=="USER2"  && jtag_cable_name =~ "Digilent Nexys4DDR 210292A4C432A"} -index 0
con

onerror {resume}
quietly WaveActivateNextPane {} 0
add wave -noupdate /testbench/SW
add wave -noupdate /testbench/Reset
add wave -noupdate /testbench/Run
add wave -noupdate /testbench/Continue
add wave -noupdate /testbench/Clk
add wave -noupdate /testbench/LED
add wave -noupdate /testbench/PC
add wave -noupdate /testbench/IR
add wave -noupdate /testbench/MAR
add wave -noupdate /testbench/MDR
add wave -noupdate /testbench/HEX0
add wave -noupdate /testbench/HEX1
add wave -noupdate /testbench/HEX2
add wave -noupdate /testbench/HEX3
add wave -noupdate /testbench/ADDR
add wave -noupdate /testbench/R0
add wave -noupdate /testbench/R1
add wave -noupdate /testbench/BUS
add wave -noupdate /testbench/HEX
add wave -noupdate /testbench/LC3/slc/d0/PC_MUX/S0
add wave -noupdate /testbench/LC3/slc/d0/PC_MUX/S1
add wave -noupdate /testbench/LC3/slc/d0/PC_MUX/S2
add wave -noupdate /testbench/LC3/slc/d0/PC_MUX/cs
add wave -noupdate /testbench/LC3/slc/PCMUX
TreeUpdate [SetDefaultTree]
WaveRestoreCursors {{Cursor 1} {279780 ps} 0}
quietly wave cursor active 1
configure wave -namecolwidth 221
configure wave -valuecolwidth 100
configure wave -justifyvalue left
configure wave -signalnamewidth 0
configure wave -snapdistance 10
configure wave -datasetprefix 0
configure wave -rowmargin 4
configure wave -childrowmargin 2
configure wave -gridoffset 0
configure wave -gridperiod 1
configure wave -griddelta 40
configure wave -timeline 0
configure wave -timelineunits ns
update
WaveRestoreZoom {0 ps} {933150 ps}

module testbench();

timeunit 10ns;
timeprecision 1ns;

logic [9:0] SW;
logic Reset, Run, Continue;
logic Clk;
logic [9:0] LED;

logic [15:0] PC;
logic [15:0] IR;
logic [15:0] MAR;
logic [15:0] MDR;
logic [6:0] HEX0, HEX1, HEX2, HEX3;
logic [19:0] ADDR;

logic [15:0] R0;
logic [15:0] R1;

logic[15:0] BUS;
logic[15:0] HEX;


slc3_testtop LC3(.Clk(Clk), .Run(Run), .Continue(Continue), .SW(SW), .HEX0(HEX0), .HEX1(HEX1), .HEX2(HEX2), .HEX3(HEX3), .LED(LED));

always_comb begin
//
	PC = LC3.slc.d0.PC_register.Data_Out;
	IR = LC3.slc.d0.IR_register.Data_Out;
	MAR = LC3.slc.d0.MAR_register.Data_Out;
	MDR = LC3.slc.d0.MDR_register.Data_Out;
//	HEX = LC3.slc.hex_4;
	MDR = LC3.slc.state_controller.State;
	BUS = LC3.slc.d0.BUS;
//	BRNZP = {LC3.slc.d0.}
//	
//
end

always begin
	#1 Clk = ~Clk;
end

initial begin	
	Clk = 0;
end



initial begin 

//	#2
//	Run = 0;
//	#2
//	Continue = 0;
//	
//
//	#2
//	Continue = 1;
//	#2
//	Run = 1;
//
//	#8
//	Continue = 0;
//	#8
//	Continue = 1;
//
//	#8
//	Continue = 0;
//	#8
//	Continue = 1;
//
//	#8
//	Continue = 0;
//	#8
//	Continue = 1;
//
//	#8
//	Continue = 0;
//	#8
//	Continue = 1;
//
//	#8
//	Continue = 0;
//	#8
//	Continue = 1;
//

#30
 Run = 1;
#2
 Continue = 1;

#2
 Run = 0;
#2
 Continue = 0;

#20
 SW = 10'h05A;

#2
 Run = 1'b1;
#2
 Run = 1'b0;
#2
 Continue = 1'b1;
#2
 Continue = 1'b0;

#100
 SW = 10'h003;
#2
 Run = 1'b1;
#2
 Run = 1'b0;
#2
 Continue = 1'b1;
#2
 Continue = 1'b0;
#400
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;

#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;


#600
 SW = 10'h002;
#2
 Run = 1'b1;
#2
 Run = 1'b0;
#2
 Continue = 1'b1;
#2
 Continue = 1'b0;

#1000
 SW = 10'h003;
#2
 Run = 1'b1;
#2
 Run = 1'b0;
#2
 Continue = 1'b1;
#2
 Continue = 1'b0;
#400
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;

#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;
#100
 Continue = 1'b1;
#2
 Continue = 1'b0;


	
end

endmodule  

module LUT_6to3(
	input logic [5:0] x,
	output logic [2:0] y
);


//Hamming weight LUT for a 6 bit input
localparam logic [63:0] bit0 = 64'h6996966996696996;
localparam logic [63:0] bit1 = 64'h8117177e177e7ee8;
localparam logic [63:0] bit2 = 64'hfee8e880e8808000;

assign y[0] = bit0[x];
assign y[1] = bit1[x];
assign y[2] = bit2[x];

endmodule 
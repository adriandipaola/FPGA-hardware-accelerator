module LUT_Wrapper(
    output logic [3:0] out
);
logic [5:0] in = 5'b10011;

LUT_6to3 lut(in, out);

endmodule
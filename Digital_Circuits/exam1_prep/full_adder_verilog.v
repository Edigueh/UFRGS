module full_adder (
    input wire x, y, z,
    output wire s, co
);
    assign s = x ^ y ^ z;
    assign co = (x & y) | ((x ^ y) & z);
endmodule

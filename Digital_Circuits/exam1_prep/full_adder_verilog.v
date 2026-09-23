module full_adder (
    input wire x, y, z,
    output wire s, co
);
    assign {s, co} = {
        x ^ y ^ z,
        (x & y) | ((x ^ y) & z)
    };
endmodule

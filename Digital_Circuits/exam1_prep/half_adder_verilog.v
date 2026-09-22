module half_adder (
    input wire x, y,
    output wire s, co
);
    assign {co, s} = {x & y, x ^ y};
endmodule

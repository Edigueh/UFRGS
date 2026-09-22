module comp_2v4b (
    input wire [3:0] a, b,
    output wire result
);
    assign result = (a == b);
endmodule

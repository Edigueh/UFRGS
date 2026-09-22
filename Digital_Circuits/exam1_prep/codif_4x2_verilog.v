module codif_4x2 (
    input wire [3:0] e,
    output wire [1:0] s
);
    assign s[1] = e[3] | e[2];
    assign s[0] = e[3] | (~e[2] & e[1]);
endmodule

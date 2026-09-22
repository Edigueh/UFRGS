module decod_2x4 (
    input wire [1:0] e,
    output wire [3:0] s
);
    // Shifts the number 1 left by 'e' positions.
    assign s = 4'b0001 << e;
endmodule

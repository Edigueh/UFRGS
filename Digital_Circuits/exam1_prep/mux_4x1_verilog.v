module mux_4x1 (
    input wire [3:0] e,
    input wire [1:0] sel,
    output wire s
);
    assign s = sel[0] ? (sel[1] ? e[3] : e[1])
                      : (sel[1] ? e[2] : e[0]);
endmodule

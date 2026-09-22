module demux_1x4 (
    input  wire e,
    input wire [1:0] sel,
    output reg [3:0] s
);
    assign s = e << sel;
endmodule

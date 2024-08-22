module FSM(input [2:0] r,
    output reg [2:0] g);
    reg [1:0] state;

    always @(r) begin
        case(state)
            0: begin
                if (r[0]==1)
                    state = 2'b01;
                else if (r[1]==1)
                    state = 2'b10;
                else if (r[2]==1)
                    state = 2'b11;
            end
            1: begin
                if (r[0]==0)
                    state = 2'b00;
            end
            2: begin
                if (r[1]==0)
                    state = 2'b00;
            end
            3: begin
                if (r[2]==0)
                    state = 2'b00;
            end
        endcase
    end

    always @(state) begin
        case(state)
            0: g = 3'b000;
            1: g = 3'b001;
            2: g = 3'b010;
            3: g = 3'b100;
        endcase
    end
endmodule
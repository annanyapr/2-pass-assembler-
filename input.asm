    START 
    MOV R2, 0003H 
    MOV R31, 0004H 
L1: ADD R2, 0001H 
    LOOP L1
    MUL R3 
    AND R2, R9 
    JMP L2 
    OR R2, R5 
L2: HLT 
    END 

    START 
    MOV R2, 0011B ; 09210888
    MOV R31, 0004H 
l1 : ADD R2, 0001H ; loda le lo
; loda le lo
    LOOP L1
    MUL R3 
    AND R2, R9 
    JMP L2 
    OR R2, R5 
L2 : HLT 
    END 

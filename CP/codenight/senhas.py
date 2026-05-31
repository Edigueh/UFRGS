n = int(input().strip())

possibilidades = [set() for _ in range(6)]

for i in range(n):
    entrada = input().strip().split()
    
    mapa = {
        'A': {entrada[0], entrada[1]},
        'B': {entrada[2], entrada[3]},
        'C': {entrada[4], entrada[5]},
        'D': {entrada[6], entrada[7]},
        'E': {entrada[8], entrada[9]}
    }
    
    letras_senha = entrada[10:16]
    
    for j in range(6):
        letra_atual = letras_senha[j]
        digitos_possiveis = mapa[letra_atual]
        
        if i == 0:
            possibilidades[j] = digitos_possiveis
        else:
            possibilidades[j] = possibilidades[j].intersection(digitos_possiveis)
            
senha_final = [list(pos)[0] for pos in possibilidades]

print(" ".join(senha_final))

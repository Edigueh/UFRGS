def descobrir_senha():
    # Lê o número de linhas N
    n = int(input().strip())
    
    # Lista de 6 conjuntos para guardar as possibilidades de cada dígito da senha
    possibilidades = [set() for _ in range(6)]
    
    for i in range(n):
        # Lê a linha e separa os elementos por espaço
        entrada = input().strip().split()
        
        # Mapeamento das letras (A, B, C, D, E) para seus respectivos pares de números
        mapa = {
            'A': {entrada[0], entrada[1]},
            'B': {entrada[2], entrada[3]},
            'C': {entrada[4], entrada[5]},
            'D': {entrada[6], entrada[7]},
            'E': {entrada[8], entrada[9]}
        }
        
        # As últimas 6 letras correspondem às 6 posições da senha
        letras_senha = entrada[10:16]
        
        for j in range(6):
            letra_atual = letras_senha[j]
            digitos_possiveis = mapa[letra_atual]
            
            if i == 0:
                # Na primeira linha, apenas atribuímos as possibilidades
                possibilidades[j] = digitos_possiveis
            else:
                # Nas linhas seguintes, pegamos apenas a interseção (o número que se repete)
                possibilidades[j] = possibilidades[j].intersection(digitos_possiveis)
                
    # Extrai o único dígito restante para cada uma das 6 posições
    senha_final = [list(pos)[0] for pos in possibilidades]
    
    # Imprime a senha separada por espaços
    print(" ".join(senha_final))

if __name__ == "__main__":
    descobrir_senha()

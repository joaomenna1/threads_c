import matplotlib.pyplot as plt

def extrair_valores_do_arquivo(nome_arquivo):
    with open(nome_arquivo, 'r') as arquivo:
        linhas = arquivo.readlines()
        if len(linhas) >= 2:
            linha_tempo_medio = linhas[-2].strip().split(':')
            linha_clientes_atendidos = linhas[-1].strip().split(':')
            if len(linha_tempo_medio) == 2 and len(linha_clientes_atendidos) == 2:
                tempo_medio = float(linha_tempo_medio[1].strip())
                clientes_atendidos = int(linha_clientes_atendidos[1].strip())
                return tempo_medio, clientes_atendidos
    return None

def plotar_grafico(tempo_medio, clientes_atendidos):
    plt.bar(['Tempo Médio de Espera', 'Clientes Atendidos'], [tempo_medio, clientes_atendidos])
    plt.ylabel('Valores')
    plt.title('Estatísticas de Atendimento')
    plt.ylim(0, tempo_medio * 1.2) 
    plt.savefig('grafico.png')

nome_arquivo = "resultado_da_simulacao.txt"
valores = extrair_valores_do_arquivo(nome_arquivo)

if valores:
    tempo_medio, clientes_atendidos = valores
    plotar_grafico(tempo_medio, clientes_atendidos)
else:
    print('Erro: Não foi possível extrair os valores do arquivo.')

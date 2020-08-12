Foi preciso criar um arquivo myhostfile para configurar o número máximo de slots, pois não estava sendo possível criar 8 processos.

Na questão 4, o tempo ficou maior com 8 processos, pois o tamanho do vetor era pequeno para avaliar o ganho com 8 processos. Por isso, testei também com vetor de tamanho 10.000.000 e o tempo foi melhor com 8 processos.
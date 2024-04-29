#Variable representando cantidad de jugadores
players_per_case:int = 10

#O(1) debido a que se trata de simlpes comparaciones de tipos primitivos
def max_abilities(formation1: tuple[tuple[list[str], list[str]], tuple[float, float]], formation2: tuple[tuple[list[str], list[str]], tuple[float, float]]):
    if formation1[1][0] > formation2[1][0]:
        return formation1
    elif formation1[1][0] < formation2[1][0]:
        return formation2
    else:
        if formation1[1][1] >= formation2[1][1]:
            return formation1
        else:
            return formation2

#Por cada jugador, el algoritmo realiza 2 llamados recursivos, por lo que tiene una totalidad de
#2^n llamados recursivos (con n la cantidad de jugadores), los cuales, en peor caso (cuando la formacion esta completa), van a 
# realizar una copia profunda del array conteniendo a los atacantes y defensores, por lo que
#tomando a=#atacantes y d=#defensores, costaria O(a + d). En resumen, la complejidad resulta
#O(2^n(d + a))
def optimal_Formation(players_info:dict[str, tuple[int,int]], player_names: list[str], curr_player:int, atackers: list[str], defenders:list[str], atack_ability:int, defend_ability:int):
    if len(atackers) > 5 or len(defenders) > 5:
        return [(), (float("-inf"), float("-inf"))]
    if len(atackers) == 5 and len(defenders) == 5:
        return [(atackers.copy(),defenders.copy()), (atack_ability, defend_ability)]
    # if curr_player >= 10:
    #     return [([], []), (float("-inf"), float("-inf"))]
    else:
        atackers.append(player_names[curr_player])
        as_atacker = optimal_Formation(players_info, player_names, curr_player + 1, atackers, defenders, atack_ability + players_info[player_names[curr_player]][0], defend_ability)
        atackers.pop() 
        defenders.append(player_names[curr_player])
        as_defender = optimal_Formation(players_info, player_names, curr_player + 1, atackers, defenders, atack_ability, defend_ability + players_info[player_names[curr_player]][1])
        defenders.pop()
        return max_abilities(as_atacker, as_defender)

def get_formation(players_info):
    player_names = list(players_info)
    #Ordeno ahora para que, cuando halla empates en cuanto a las habilidades de dos formaciones diferentes
    #La primera este formada por los jugadores que vienen antes alfabeticamente
    player_names.sort() #O(nlogn)
    result = optimal_Formation(players_info, player_names, 0, [], [], 0, 0)
    atackers = result[0][0]
    defenders = result[0][1]
    atacker_output = "(" + ", ".join(atackers) + ")"
    defenders_output = "(" + ", ".join(defenders) + ")"
    return atacker_output + "\n" + defenders_output

    

if __name__ == "__main__":
    num_cases: int = input()      
    output: list[str] = []
    for case in range(int(num_cases)):
        #Un diccionario para guardar los nombres de los jugadores y sus habilidades
        #Como sabemos que el vocabulario esta acotado, asi como la longitud de los nombres
        #El acceso se logra en tiempo constante (O(1))
        case_dict:dict[str, tuple[int,int]] = {}
        for player in range(players_per_case):
            player_name, atacking_ability, defending_ability = input().split(" ")
            atacking_ability = int(atacking_ability)
            defending_ability = int(defending_ability)
            case_dict[player_name] = (atacking_ability, defending_ability)
            l = list(case_dict)
            l.sort()
        res = get_formation(case_dict)
        output.append(f"Case {case + 1}:\n" + res)
    for o in output:
        print(o)
   
    
        
      
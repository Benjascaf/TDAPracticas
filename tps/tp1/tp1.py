#Variable representando cantidad de jugadores
players_per_case:int = 10

def getFormation(players_info:dict[str, tuple[int,int]]) -> str:
    player_names: list[str] = list(players_info)
    #Ordeno de manera descendiente para que en caso de empate elija el jugador adecuado
    #Uso sort pero si esto fuese a ser marcado como un problema lo que hubiese hecho
    #es nuevamente radix sort ya que gracias a la longitud y vocabulario acotados
    #la complejidad de sortear el array de tamano n quedaria O(n)
    player_names.sort(reverse=True) 
    #La abilidad de cada jugador tambien esta acotada, por lo q aprovecho y uso radix sort
    #Aunque mucha diferencia no deberia de haber debido al tamano del input.
    radix_sort_players(players_info, player_names, 1)
    radix_sort_players(players_info, player_names, 0)
    atackers = player_names[5:]
    defenders = player_names[:5]
    #Nuevamente ordeno para obtener el output deseado
    atackers.sort()
    defenders.sort()
    atackers_output = "(" + ", ".join(atackers) + ")"
    defenders_output ="(" + ", ".join(defenders) + ")"
    return atackers_output + "\n" + defenders_output
def counting_sort_players(players_info:dict[str, tuple[int,int]], player_names: list[str], sort_by: int, exp:int):
    global players_per_case
    bucket: list[list[str]] = [[] for _ in range(players_per_case)]
    for player_name in player_names:
        player_ability = players_info[player_name][sort_by]
        index = (player_ability // exp) % 10
        #Los mejores defensores quiero q esten al principio de la lista
        #Asi q los ordeno de manera descendiente
        if sort_by == 1: 
            index = players_per_case - 1 - index
        bucket[index].append(player_name)
    res: list[str] = []
    for i in range(len(bucket)):
        for player in bucket[i]:
            res.append(player)
    for i in range(players_per_case):
        player_names[i] = res[i]

def radix_sort_players(players_info:dict[str, tuple[int,int]], player_names: list[str], sort_by: int):
    max_exp = 10 
    exp = 1 
    while exp <= max_exp:
        counting_sort_players(players_info, player_names, sort_by, exp)
        exp *= 10

if __name__ == "__main__":
    num_cases: int = input()
    output: list[str] = []
    for case in range(int(num_cases)):
        case_dict:dict[str, tuple[int,int]] = {}
        for player in range(players_per_case):
            player_name, atacking_ability, defending_ability = input().split(" ")
            atacking_ability = int(atacking_ability)
            defending_ability = int(defending_ability)
            case_dict[player_name] = (atacking_ability, defending_ability)
        output.append(f"Case {case + 1}:\n" + getFormation(case_dict))
    for o in output:
        print(o)
   
    
        
    
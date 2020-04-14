import os
os.environ.setdefault("DJANGO_SETTINGS_MODULE", "proj4_extra.settings")
import django
django.setup()

from db_extra.models import Player, Team, Color, State


def printResult(res):
    for unit in res:
        for i in unit:
            print(i, end = ' ')
        print('')
    return

def query1(use_mpg, min_mpg, max_mpg, use_ppg, min_ppg, max_ppg, use_rpg,
           min_rpg, max_rpg, use_apg, min_apg, max_apg, use_spg, min_spg,
           max_spg, use_bpg, min_bpg, max_bpg):

    print("PLAYER_ID TEAM_ID UNIFORM_NUM FIRST_NAME LAST_NAME MPG PPG RPG APG SPG BPG")
    maxi = 2147483647
    mini = -1
    if use_mpg == 0:
        min_mpg = mini
        max_mpg = maxi
    if use_rpg == 0:
        min_rpg = mini
        max_rpg = maxi
    if use_apg == 0:
        min_apg = mini
        max_apg = maxi
    if use_spg == 0:
        min_spg = mini
        max_spg = maxi
    if use_bpg == 0:
        min_bpg = mini
        max_bpg = maxi
    if use_ppg == 0:
        min_ppg = mini
        max_ppg = maxi
    players = Player.manager.filter(mpg__lte = max_mpg, mpg__gte = min_mpg,
                                    ppg__lte = max_ppg, ppg__gte = min_ppg,
                                    rpg__lte = max_rpg, rpg__gte = min_rpg,
                                    apg__lte = max_apg, apg__gte = min_apg,
                                    spg__lte = max_spg, spg__gte = min_spg,
                                    bpg__lte = max_bpg, bpg__gte = min_bpg).values_list("player_id", "team_id",
                                                                                        "uniform_num", "first_name",
                                                                                        "last_name", "mpg", "ppg",
                                                                                        "rpg", "apg", "spg", "bpg")
    printResult(players)
    return

def query2(team_color):
    teams = Team.manager.filter(color_id_id__name = team_color).values_list('name')
    print('NAME')
    printResult(teams)
    return

def query3(team_name):
    players = Player.manager.filter(team_id__name = team_name).order_by('-ppg').values_list('first_name', 'last_name')
    print('FIRST_NAME LAST_NAME')
    printResult(players)
    return

def query4(team_state, team_color):
    
    players = Player.manager.filter(team_id__state_id__name = team_state,
                                    team_id__color_id__name = team_color,).values_list('first_name', 'last_name', 'uniform_num')
    print('FIRST_NAME LAST_NAME UNIFORM_NUM')
    printResult(players)
    return

def query5(wins):
    #players = Player.manager.select_related('team_id__name')
    players = Player.manager.filter(team_id__wins__gt = wins).values_list('first_name', 'last_name', 'team_id__name', 'team_id__wins')
    print('FIRST_NAME LAST_NAME TEAM_NAME WINS')
    printResult(players)

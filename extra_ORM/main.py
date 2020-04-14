import os
os.environ.setdefault("DJANGO_SETTINGS_MODULE", "proj4_extra.settings")
import django
django.setup()
import exercise

from db_extra.models import Player, Team, Color, State

def buildPlayer(filename):
    file = open(filename)
    for l in file:
        attributes = l.split(' ')
        Player.manager.create_player(attributes[0], Team.manager.get(team_id = attributes[1]), attributes[2],
                                      attributes[3], attributes[4], attributes[5], attributes[6],
                                     attributes[7], attributes[8], attributes[9], attributes[10])
    file.close()
    return

def buildTeam(filename):
    file = open(filename)
    for l in file:
        attributes = l.split(' ')
        Team.manager.create_team(attributes[0], attributes[1], State.manager.get(state_id = attributes[2]),
                                   Color.manager.get(color_id = attributes[3]), attributes[4], attributes[5])
    file.close()
    return

def buildColor(filename):
    file = open(filename)
    for l in file:
        attributes = l.split(' ')
        attributes[1] = attributes[1].replace('\n', '')
        Color.manager.create_color(attributes[0], attributes[1])
    file.close()
    return

def buildState(filename):
    file = open(filename)
    for l in file:
        attributes = l.split(' ')
        attributes[1] = attributes[1].replace('\n', '')
        State.manager.create_state(attributes[0], attributes[1])
    file.close()
    return
    
def main():
    buildColor('color.txt')
    buildState('state.txt')

    buildTeam('team.txt')
    buildPlayer('player.txt')
    exercise.exercise()
if __name__ == "__main__":
    main()

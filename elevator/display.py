#ul = up_light
#dl = down_light
#ew = elevator_wall
#ewd = elevator_wall_door
#fd = floor_door
#ec = elevator_ceiling

button_display = f"""

"""

floor_display = f"""
-------------
############# __________
-------------| {ew + ec*6  + ew} |   
|        {ul}{fd} {ewd + " "*6 + ew} |
|        {dl}{fd} {ewd + " "*6 + ew} |
-------------| {ewd + ec*6  + ew} |
#############|
-------------|   
"""

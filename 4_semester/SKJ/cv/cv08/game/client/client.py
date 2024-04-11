import xmlrpc.client
import random
import visualizer
import xml.etree.ElementTree as ET

class Agent:
    def __init__(self, filename):
        tree = ET.parse(filename)
        root = tree.getroot()

        self.login = root.find('login').text
        server_url = root.find('url').text
        
        self.data = []
        self.visualizer = visualizer.Visualizer()
        
        self.gameserver = xmlrpc.client.ServerProxy(server_url)
        
        self.gameserver.add_player(self.login)

    def action(self):
        action_result = self.gameserver.make_action(self.login, "look", "")
        self.visualizer.visualize(action_result)
    
    def __repr__(self):
        return str(self.data)

def save_data(self):
    with open('data.txt', 'w') as f:
        for item in self.data:
            f.write("%s\n" % item)


class AgentRandom(Agent):
    def action(self):
        direction = random.choice(['north', 'west', 'south', 'east'])
        action_result = self.gameserver.make_action(self.login, "move", direction)
        self.visualizer.visualize(action_result)

class AgentLeftRight(Agent):
    def __init__(self, filename):
        super().__init__(filename)
        self.direction = 'west'

    def action(self):
        action_result = self.gameserver.make_action(self.login, "move", self.direction)
        if len(self.data) > 5 and len(self.data[5]) > 5:
            barrier = self.data[5][4] if self.direction == 'west' else self.data[5][6]

            if barrier in ['t', 'o', '~']:
                self.direction = 'east' if self.direction == 'west' else 'west'
                if self.direction == 'east':
                    action_result = self.gameserver.make_action(self.login, "move", "west")
                else:
                    action_result = self.gameserver.make_action(self.login, "move", "east")

        self.visualizer.visualize(action_result)

def main():
    agent = None
    try:
        # agent = Agent('config.xml')
        # agent = AgentRandom('config.xml')
        agent = AgentLeftRight('config.xml')
        while agent.visualizer.running:
            agent.action()
            print(agent)
        else:
            agent.gameserver.make_action(agent.login, 'exit', '')

        agent.save_data()
    except KeyboardInterrupt:
        agent.gameserver.make_action(agent.login, 'exit', '')


if __name__ == '__main__':
    main()

from xmlrpc.server import SimpleXMLRPCServer


class Forecast(object):
    def __init__(self, description, wind_force, temperature):
        self.description = description
        self.wind_force = wind_force
        self.temperature = temperature

    def get_list(self):
        return [self.description, self.wind_force, self.temperature]


class ForecastCalendar(object):
    def __init__(self, initial_values, password):
        self.init = initial_values
        self.password = password

    def get_forecast(self, date):
        forecast = self.init.get(date)
        if forecast:
            return str(forecast.get_list())
        else:
            return "No forecast"

    def update_forecast(self, password, date, description, wind_force, temperature):
        if password != self.password:
            return "No update"
        else:
            self.init[date] = Forecast(description, wind_force, temperature)
            return "Forecast updated"


def main():
    initial_state = {
        "2012-11-05": Forecast('Sunny', 10, 20),
        "2012-11-06": Forecast('Cloudy', 15, 25),
        "2012-11-07": Forecast('Sunny', 10, 20)
    }

    fcalendar = ForecastCalendar(initial_state, password="master-of-weather")

    server_address = ('localhost', 10001)
    server = SimpleXMLRPCServer(server_address)
    server.register_instance(fcalendar)
    server.register_introspection_functions()
    print("Starting Weather XML-RPC server, use <Ctrl-C> to stop")
    server.serve_forever()


if __name__ == "__main__":
    main()
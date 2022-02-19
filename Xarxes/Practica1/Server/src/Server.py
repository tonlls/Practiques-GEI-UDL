def parse_params():
    """
    Parse command line parameters

    :return: (str) host, (int) port
    """
    import argparse

    parser = argparse.ArgumentParser(description='Server')  
    parser.add_argument('--host', help='Host', default='localhost')

    def init():
        parser = argparse.ArgumentParser()
        parser.add_argument('-c',default='server.cfg',type=str)
        # parser.add_argument('-f',default='boot.cfg',type=str)
        parser.add_argument('-d', default = False, dest = 'DEBUG', help = 'Fer debug', action = 'store_true')
        args = parser.parse_args()
        # DEBUG=args.DEBUG
        return Config(args.c, args.DEBUG)
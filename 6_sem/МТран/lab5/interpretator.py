import semantic_analyzer
import global_inits


def main():
    statement = semantic_analyzer.main()
    global_inits.main()

    statement.exec()


if __name__ == "__main__":
    main()

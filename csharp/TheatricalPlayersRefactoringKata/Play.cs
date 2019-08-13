namespace TheatricalPlayersRefactoringKata
{
    public class Play
    {
        private string _name;
        private string _type;

        public string Name { get => _name; set => _name = value; }
        public string Type { get => _type; set => _type = value; }

        public Play(string name, string type) {
            this._name = name;
            this._type = type;
        }
    }
}

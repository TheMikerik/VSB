import Distribution.Simple.LocalBuildInfo (Component)
import Distribution.Compat.Lens (_1)
data HTML = Attribute {atribName :: String, valueHTML :: String}
          | Tag {tagName :: String, firstList :: [HTML], scndList :: [HTML]}
          | HTMLDocument [HTML] deriving (Show)

testHTML = HTMLDocument [ Tag {tagName = "body",
                        firstList = [Attribute {atribName = "textNumber=", valueHTML = "seven"},
                        Attribute {atribName = "color=", valueHTML = "yellow"}],
                        scndList = [Attribute {atribName = "button=", valueHTML = "Close"}]}]

data Component2 = TextBox {name :: String, text :: String}
                | Button {name :: String, value :: String}
                | Container {name :: String, children :: [Component2]}

gui :: Component2
gui = Container "My App" [
        Container "Menu" [
            Button "btn_new" "New",
            Button "btn_open" "Open",
            Button "btn_close" "Close"],
        Container "Body" [TextBox "textbox_1" "Some text goes here"],
        Container "Footer" []]

listButtonNames :: Component2 -> [String]
listButtonNames (Button x _) = [x]
listButtonNames (Container _ xs) = listButtonNames `concatMap` xs
listButtonNames TextBox {} = []


--changeText :: Component2 -> String -> String -> Component2
--changeText (Button name text) _ _ = Button name text
--chngeText (TextBox name text) newName newText = case name == newName of
--                             Just -> TextBox name newName
--                             Nothing -> Textbox name text
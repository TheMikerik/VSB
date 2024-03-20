import xml.etree.ElementTree as ET
root = ET.Element('todos', {'name':'ukoly'})
task = ET.Element('task')
task.text = 'Umyt nadobi'

root.append(task)

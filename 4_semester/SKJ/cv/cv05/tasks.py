import xml.etree.ElementTree as ET

# 4
def create_student(xml_root, student_id):
    for student in xml_root.findall('student'):
        if student.attrib['student_id'] == student_id:
            raise Exception('student already exists')
    xml_root.append(ET.Element('student', {'student_id': student_id}))


# 3
def remove_student(xml_root, student_id):
    for student in xml_root.findall('student'):
        if student.attrib['student_id'] == student_id:
            xml_root.remove(student)

# 6
def set_task_points(xml_root, student_id, task_id, points):
    for student in xml_root.findall('student'):
        if student.attrib['student_id'] == student_id:
            for task in student.findall('task'):
                if task.attrib['task_id'] == task_id:
                    task.text = points
    pass

# 8
def create_task(xml_root, student_id, task_id, points):
    '''
    Pro daného studenta vytvořte task s body.
    Ujistěte se, že task (s task_id) u studenta neexistuje, jinak: raise Exception('task already exists')
    '''
    for student in xml_root.findall('student'):
        if student.attrib['student_id'] == student_id:
            for task in student.findall('task'):
                if task.attrib['task_id'] == task_id:
                    raise Exception('task already exists')
                student.append(ET.Element('task', {'task_id': task_id}))
                for tasks in student.findall('task'):
                    if tasks.attrib['task_id'] == task_id:
                        tasks.text = points
    pass

# 4
def remove_task(xml_root, task_id):
    for student in xml_root.findall('student'):
        for task in student.findall('task'):
            if task.attrib['task_id'] == task_id:
                student.remove(task)

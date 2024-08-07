using System;
using System.Collections.Generic;

namespace LMS.Models.LMSModels;

public partial class Department
{
    public uint DepartmentId { get; set; }

    public string? Name { get; set; }

    public string? SubjectAbbreviation { get; set; }

    public virtual ICollection<Course> Courses { get; set; } = new List<Course>();

    public virtual ICollection<Professor> Professors { get; set; } = new List<Professor>();

    public virtual ICollection<Student> Students { get; set; } = new List<Student>();
}

using System;
using System.Collections.Generic;

namespace LMS.Models.LMSModels;

public partial class Course
{
    public uint CourseId { get; set; }

    public string? Name { get; set; }

    public int? Number { get; set; }

    public uint DepartmentId { get; set; }

    public virtual ICollection<Class> Classes { get; set; } = new List<Class>();

    public virtual Department Department { get; set; } = null!;
}

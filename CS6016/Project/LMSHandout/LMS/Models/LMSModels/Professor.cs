using System;
using System.Collections.Generic;

namespace LMS.Models.LMSModels;

public partial class Professor
{
    public string ProfessorId { get; set; } = null!;

    public string? FirstName { get; set; }

    public string? LastName { get; set; }

    public DateOnly? Dob { get; set; }

    public uint DepartmentId { get; set; }

    public virtual ICollection<Class> Classes { get; set; } = new List<Class>();

    public virtual Department Department { get; set; } = null!;

    public virtual User ProfessorNavigation { get; set; } = null!;
}

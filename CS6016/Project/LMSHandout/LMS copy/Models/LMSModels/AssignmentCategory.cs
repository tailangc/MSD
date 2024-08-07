using System;
using System.Collections.Generic;

namespace LMS.Models.LMSModels;

public partial class AssignmentCategory
{
    public uint CategoriesId { get; set; }

    public uint ClassId { get; set; }

    public string? CategoryName { get; set; }

    public decimal Weight { get; set; }

    public virtual ICollection<Assignment> Assignments { get; set; } = new List<Assignment>();

    public virtual Class Class { get; set; } = null!;
}

using System;
using System.Collections.Generic;

namespace LMS.Models.LMSModels;

public partial class User
{
    public string UId { get; set; } = null!;

    public string? FirstName { get; set; }

    public string? LastName { get; set; }

    public DateOnly? Dob { get; set; }

    public virtual Administrator? Administrator { get; set; }

    public virtual Professor? Professor { get; set; }

    public virtual Student? Student { get; set; }
}

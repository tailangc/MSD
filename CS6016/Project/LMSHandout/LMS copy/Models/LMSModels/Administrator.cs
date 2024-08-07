﻿using System;
using System.Collections.Generic;

namespace LMS.Models.LMSModels;

public partial class Administrator
{
    public string AdminId { get; set; } = null!;

    public string? FirstName { get; set; }

    public string? LastName { get; set; }

    public DateOnly? Dob { get; set; }

    public virtual User Admin { get; set; } = null!;
}

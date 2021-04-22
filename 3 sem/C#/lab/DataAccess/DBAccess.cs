﻿using System;
using Models;
using Models.Result;

namespace DataAccess
				try
				{
					connection.Open();

					var preSqlCommand = Parser.LazyParse<PreSqlCommand>(commandPath);
					SqlCommand command = preSqlCommand.ToSqlCommand();
					command.Connection = connection;

					var assembly = typeof(Order).Assembly;

					var type = assembly.GetType(preSqlCommand.Model);

					if (type is null)
					{
						type = assembly.GetType("Models." + preSqlCommand.Model, true);
					}

					MethodInfo execute = typeof(SqlCommandExtensions).GetMethod("Execute", BindingFlags.Public | BindingFlags.Static);
					execute = execute.MakeGenericMethod(type);


					var res = new Result<T>()
					{
						Table = execute.Invoke(null, new object[] { command }) as IEnumerable<T>,
						TypeOfTable = type
					};

					return res;
				}
				catch (Exception ex)
				{
					throw ex;
				}
				finally
				{
					connection.Close();
				}